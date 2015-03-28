If you need to work on large xml-files streamed from the disc without DOM and you want to have speeds known from RapidXml or a similar api, then have a look on EagleXml.

This project simply takes the source of RapidXml and modifies it. The result should then have the desired properties. :)


Lets have an example! Imagine the following xml file
```
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<root>
  <content>Hello World</content>
</root>
```

```
// choose parser flags (known from rapidxml)
static const int parser_flags = eaglexml::parse_no_data_nodes
                              | eaglexml::parse_normalize_whitespace
                              | eaglexml::parse_trim_whitespace
                              | eaglexml::parse_validate_closing_tags
                              | eaglexml::parse_default;

// open a file stream to a xml file
std::ifstream xml_stream("test.xml");

// create a cache
eaglexml::stream_cache<> cache(xml_stream, 8 * 1024 * 1024);

// setup the document
eaglexml::xml_document<> document;
document.parse<parser_flags>(&cache);

// note that the parser will not load the hole file!
// only tags that are examined will be loaded
eaglexml::xml_node<>* root_node = document.first_node("root");
eaglexml::xml_node<>* content_node = root_node->first_node("content");
std::string content = content_node->value();

std::cout << content << std::endl;

```