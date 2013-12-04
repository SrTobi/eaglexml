#ifndef EAGLEXML_UTILS_HPP_INCLUDED
#define EAGLEXML_UTILS_HPP_INCLUDED

// Copyright (C) 2012 Tobias Kahlert
// Version 0.1
//! \file eaglexml_rapidexport.hpp This file contains some export function to export
//! hole eaglexml nodes to rapidxml.

#include <rapidxml.hpp>
#include <stdexcept>
#include "eaglexml.hpp"

namespace eaglexml
{


	template<typename Ch_or_CacheType = EAGLEXML_STD_CHAR_TYPE>
	class xml_exporter
	{
	public:
		typedef typename internal::extract_char<Ch_or_CacheType>::char_type	char_type;

		typedef rapidxml::memory_pool<char_type>					memory_pool;
	public:
		xml_exporter(memory_pool* pool)
			: m_pool(pool)
		{}


		rapidxml::xml_attribute<char_type>* export_attribute(eaglexml::xml_attribute<Ch_or_CacheType>* attr)
		{
			char_type* attr_name = m_pool->allocate_string(attr->name(), attr->name_size());
			char_type* attr_value = m_pool->allocate_string(attr->value(), attr->value_size());

			return m_pool->allocate_attribute(attr_name, attr_value, attr->name_size(), attr->value_size());
		}


		rapidxml::xml_node<char_type>* export_node(	eaglexml::xml_node<Ch_or_CacheType>* node,
													bool exportChildren = true,
													bool exportAttributes = true)
		{
			char_type* name = m_pool->allocate_string(node->name(), node->name_size());
			char_type* value = m_pool->allocate_string(node->value(), node->value_size());

			rapidxml::xml_node<char_type>* rapid_node = m_pool->allocate_node(	ConvType(node->type()),
																				name,
																				value,
																				node->name_size(),
																				node->value_size());

			if(exportAttributes)
			{
				// Export attributes
				for(eaglexml::xml_attribute<Ch_or_CacheType>* it = node->first_attribute();
					it;
					it = it->next_attribute())
				{
					rapid_node->append_attribute(export_attribute(it));
				}
			}

			if(exportChildren)
			{
				// Export children
				for(eaglexml::xml_node<Ch_or_CacheType>* it = node->first_node();
					it;
					it = it->next_sibling())
				{
					rapid_node->append_node(export_node(it));
				}
			}

			return rapid_node;
		}

		void export_to_document(eaglexml::xml_node<Ch_or_CacheType>* node, rapidxml::xml_document<char_type>* target)
		{
			// Export children
			for(eaglexml::xml_node<Ch_or_CacheType>* it = node->first_node();
				it;
				it = it->next_sibling())
			{
				target->append_node(export_node(it));
			}
		}

		
		static rapidxml::node_type ConvType(eaglexml::node_type type)
		{
			switch(type)
			{
			case node_document:		return rapidxml::node_document;
			case node_element:		return rapidxml::node_element;
			case node_data:			return rapidxml::node_data;
			case node_cdata:		return rapidxml::node_cdata;
			case node_comment:		return rapidxml::node_comment;
			case node_declaration:	return rapidxml::node_declaration;
			case node_doctype:		return rapidxml::node_doctype;
			case node_pi:			return rapidxml::node_pi;
			default:
				throw std::invalid_argument("node-type does not exists!");
			}
		}

	private:
		memory_pool* m_pool;
	};


	template<typename Ch_or_CacheType>
	inline rapidxml::xml_document<typename internal::extract_char<Ch_or_CacheType>::char_type>&
		operator << 
			(rapidxml::xml_document<typename internal::extract_char<Ch_or_CacheType>::char_type>& doc,
			 eaglexml::xml_node<Ch_or_CacheType>* node)
	{
		eaglexml::xml_exporter<Ch_or_CacheType> exporter(&doc);

		exporter.export_to_document(node, &doc);

		return doc;
	}

	template<typename Ch_or_CacheType>
	inline rapidxml::xml_node<typename internal::extract_char<Ch_or_CacheType>::char_type>&
		operator << 
			(rapidxml::xml_node<typename internal::extract_char<Ch_or_CacheType>::char_type>& to,
			 eaglexml::xml_node<Ch_or_CacheType>* from)
	{
		eaglexml::xml_exporter<Ch_or_CacheType> exporter(to.document());

		to.append_node(exporter->export_node(from));

		return to;
	}

	template<typename Ch_or_CacheType>
	inline rapidxml::xml_node<typename internal::extract_char<Ch_or_CacheType>::char_type>&
		operator << 
		(rapidxml::xml_node<typename internal::extract_char<Ch_or_CacheType>::char_type>& to,
		eaglexml::xml_attribute<Ch_or_CacheType>* from)
	{
		eaglexml::xml_exporter<Ch_or_CacheType> exporter(to->document());

		to->append_attribute(exporter->export_attribute(from));

		return to;
	}
}


#endif
