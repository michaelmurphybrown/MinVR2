This directory contains the VRDataIndex code, a dynamically-typed
system for naming and storing data within the strongly-typed world of
C++.  In terms of its treatment of types, it's sort of like an
interpreter -- think Javascript, or Lisp, depending on your age --
without the procedural commands of a language.

The data index supports namespaces, allowing it to be used for
configuring complicated systems, with lots of individual entities.
You can define a set of global defaults that can be overridden by
individual entities, or by groups of entities.  The data index can be
exported to a character-string, in a vaguely XML syntax, and can be
read back in that same syntax.  This makes it ideal both for
configuration files, and for inter-process communication.

Tom Sgouros 12/13/15


--------------------------------------------

BASIC USAGE

To understand what's going on here, start with the documentation in
the VRDataIndex.h file.  Very roughly, the procedure is this:

Create an index:

  VRDataIndex *in = new VRDataIndex;

Add objects to it:

  in->addData("/cora/nora", 4);
  in->addData("/cora/flora", "gosh and golly");
  in->addData("/cora/dora", 2.3);

This creates a container object called "cora" that contains three
atomic objects called "nora", "flora", and "dora", contiaining an
integer, a string, and a double, respectively.  You can also do this:

  VRIntArray leonora;
  leonora.push_back(1);
  leonora.push_back(2);
  leonora.push_back(3);
  in->addData("/cora/leonora", leonora);

This adds an integer array called "leonora" to the "cora" object.  It
contains the values [1, 2, 3].  Notice that there are now five objects
in the index: the four data values, and also the container (cora) that
holds them all.  The container is added implicitly, though you can
create empty containers if you really ache to do so.

To get the values back, use getValue:

  int m = in->getValue("/cora/nora");
  VRIntArray l = in->getValue("/cora/leonora");
  std::cout << (double)in->getValue("/cora/dora");

Note the typing or casts that are necessary for the system to know
what type of data to return.

In addition to the value, you can get the type of each data value, and
you can query a container for its contents, which is basically the
same as asking for its value:

  std::cout << "Cora is a " << in->getTypeString("/cora")
  if (in->getType("/cora") == VRCORETYPE_CONTAINER) ...
  std::list<std::string> nameList = in->getValue("/cora")

This last returns a list like this:

  /cora/nora
  /cora/flora
  /cora/dora
  /cora/leonora

That is, the names within a container are absolute names, defined
relative to "/", the root namespace.  The cora object defines a
"namespace" called "/cora/".  You can think of a namespace as a
container name with a slash appended.  All the accessor functions
have a namespace version to use:

  int m = in->getValue("nora", "/cora/");
  std::string s = in->getTypeString("cora", "/")

This version looks for the value of the variable "nora" inside the
namespace "/cora/".  This becomes interesting in cases where there is
no such variable.  If you ask for a value called "lora" that does not
exist in "/cora/", the system will not return an error before checking
to see if there is a "lora" in any of the namespaces senior to
"/cora/".  In this case, there was a "/lora" defined, and so that
value is returned.

  in->addData("/lora", 37);
  int n = in->getValue("lora", "/cora/");  ==>  n = 37

You can override those values:

  in->addData("/lora", 37);
  in->addData("/cora/lora", 14);
  int n = in->getValue("lora", "/cora/");  ==>  n = 14


INPUT AND OUTPUT

Any object in the index can be "serialized", turned into a string
representation of that object, including names and values.  The
serialized versions can be readily turned back into index entries.
You can use this to send and receive values from other processes, and
to read data in from a file.  The serialized format looks more or less
like XML, though there is no template or schema document:

<cora type="container">
  <nora type="int">4</nora>
  <flora type="string">gosh and golly</flora>
  <dora type="double">2.3</dora>
</cora>

There is a queue class for communicating data in time order:

  VRDataQueue *q = new VRDataQueue;
  in->addData("/cora/nora", 4);
  q->push( in->serialize("cora", "/") );
  in->addData("/cora/nora", 6);
  q->push( in->serialize("cora", "/") );

The queue now contains two different serialized versions of "cora",
one of which has "cora/nora" set to 4 and the other set to 6.  The
queue itself has a serialize() method, so the entire queue can be
packed up and sent to another process or another machine.

  std::string qpacked = q->serialize();

When these are unpacked, they'll come out in the right time order.

  VRDataQueue *newq = new VRDataQueue(qpacked);
  VRDataIndex *remoteIndex = new VRDataIndex;

  remoteIndex->addSerializedValue(newq->getSerializedObject());
  int n = remoteIndex->getValue("/cora/nora")  ==> n = 4
  newq-pop();
  remoteIndex->addSerializedValue(newq->getSerializedObject());
  int n = remoteIndex->getValue("/cora/nora")  ==> n = 6
  


