Tutorial
========

Welcome to the tutorial. Do you want do parse xml data? Ok, you are right here. Do you want to parse xml data into a dom tree?
Ok, you better use [RapidXml](http://rapidxml.sourceforge.net/)! Do you want to access xml data dom-style
but only want to go through the tree sequentially? Ahhh... ok, stay calm. Do you want to parse large xml data or
only want to have some parts in memory? Yea, you are right here! If you don't want to, I recommand [RapidXml](http://rapidxml.sourceforge.net/).

Ok, let's get started. Of course we want to parse xml data. This data is of course located in a file.
Remember! If the data were already in memory, we would want to use [RapidXml](http://rapidxml.sourceforge.net/).
Our file has the unexpected name "example.xml". It contains some data:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.xml}

<?xml version="1.0"?>
<settings>
	<option key="width">800</option>
	<option key="height">600</option>

	<!-- I am a comment -->
	<option key=""></option>
	<option key=""></option>
</settings>

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


To parse that stuff we need to include eaglexml.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
#include <eaglexml.hpp>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

That was totally easy. The next step is easy, too.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
std::ifstream settingsInputStream("example.xml");
eaglexml::stream_cache<> xmlCache(settingsInputStream);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ok, we created an input stream to read the setting file.
We also created an stream_cache to manage the stream.

Next step is to create a xml_document which will represent the xml data.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
eaglexml::xml_document<> doc;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

doc is now our root node. But we need to attach the cache to traverse the xml DOM tree.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
doc.parse<eaglexml::parse_trim_whitespace | eaglexml::parse_normalize_whitespace>(&cache);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
eaglexml::xml_node<>* sttings_node = doc.first_node("settings");

// Check if settigs are present
if(!settings_node)
{
	
	return 1;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~