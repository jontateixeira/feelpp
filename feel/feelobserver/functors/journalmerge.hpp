// This file is part of the Feel library
//
// Author(s): Feel++ Contortium
//      Date: 2017-07-10
//
// @copyright (C) 2017 University of Strasbourg
// @copyright (C) 2012-2017 Feel++ Consortium
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA


#ifndef FEELPP_JOURNALMERGE_HPP
#define FEELPP_JOURNALMERGE_HPP 1

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>

namespace Feel
{
namespace Observer
{
namespace pt =  boost::property_tree;

//! Merge property tree pb into pa recursively.
//! Extend mathematical operation.
//! Note: property_tree does not support boolean operation currently 
//! (union, intersection, ...)
inline void ptMerge( pt::ptree& pa, const pt::ptree& pb )                                                                                                                                                    
{                                                                                                                                                                                              
    for( const auto& b: pb )                                                                                                                                                                   
    {                                                                                                                                                                                          
        bool skip = false;                                                                                                                                                                     
        for( auto& a: pa )                                                                                                                                                                     
        {                                                                                                                                                                                      
            if( a.first == b.first )                                                                                                                                                           
            {                                                                                                                                                                                  
                if( b.second.empty() )                                                                                                                                                         
                    break;                                                                                                                                                                     
                ptMerge( a.second, b.second );                                                                                                                                                
                skip = true;                                                                                                                                                                   
            }                                                                                                                                                                                  
        }                                                                                                                                                                                      
        if( not skip)                                                                                                                                                                          
            pa.put_child( b.first, b.second );                                                                                                                                                 
    }                                                                                                                                                                                          
};                                                                                                                                                                                             

//! Functor that retrieve property trees generated by JournalWatcher, then
//! merge them into a unique property tree.
//! NOTE: Each property tree have to define a "typename" key, and a "name" key.
//! \code
//! <typename> : {
//!     <name> : {
//!              ...
//!          }
//!   }"
//! \endcode
//! will be the root path for each tree.
struct JournalMerge
{
        using result_type = pt::ptree;
        result_type p;

        template<typename Iterator>
            result_type operator()( Iterator ptree_it, Iterator ptree_last ) const
            {
                pt::ptree gp;
                while( ptree_it != ptree_last )
                {
                    ptMerge( gp, *ptree_it );
                    ++ptree_it;
                }
                return gp;
            }
};


} // Observer namespace
} // Feel namespace.

#endif // FEELPP_JOURNALMERGE_HPP

// MODELINES
// -*- mode: c++; coding: utf-8; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4; show-trailing-whitespace: t
// -*- vim: set ft=cpp fenc=utf-8 sw=4 ts=4 sts=4 tw=80 et cin cino=N-s,c0,(0,W4,g0: