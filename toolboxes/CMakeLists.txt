###  CMakeLists.txt; coding: utf-8 --- 

#  Author(s): Christophe Prud'homme <christophe.prudhomme@feelpp.org>
#       Date: 05 Jan 2017
#
#  Copyright (C) 2017 Feel++ Consortium
#
# Distributed under the GPL(GNU Public License):
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
#

cmake_minimum_required(VERSION 2.8)

project(toolboxes)
set(PROJECT_SHORTNAME "toolbox")

# with this it is possible to compile applications/models from an installed
# version of feel++. This is useful also for staged compilation for docker
if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
  find_package(Feel++ PATHS ${FEELPP_DIR}/share/feelpp/feel/cmake/modules $ENV{FEELPP_DIR}/share/feelpp/feel/cmake/modules /usr/share/feelpp/feel/cmake/modules /usr/local/share/feelpp/feel/cmake/modules )
  if(NOT FEELPP_FOUND)
      message(FATAL_ERROR "Feel++ was not found on your system. Make sure to install it and specify the FEELPP_DIR to reference the installation directory.")
  endif()
endif()


option(FEELPP_TOOLBOXES_ENABLE_MESHALE "Enable/Disable mesh ALE" ON)
if ( FEELPP_TOOLBOXES_ENABLE_MESHALE )
  set(FEELPP_MODELS_HAS_MESHALE 1)
  set(FEELPP_TOOLBOXES_HAS_MESHALE_HARMONICEXTENSION 1)
  set(FEELPP_TOOLBOXES_HAS_MESHALE_WINSLOW 1)
endif()

option(FEELPP_TOOLBOXES_ENABLE "Enable/Disable Heat" ON)
option(FEELPP_TOOLBOXES_ENABLE_HEAT "Enable/Disable Heat" ON)
option(FEELPP_TOOLBOXES_ENABLE_ELECTRIC "Enable/Disable Electric" ${FEELPP_TOOLBOXES_ENABLE})
option(FEELPP_TOOLBOXES_ENABLE_THERMOELECTRIC "Enable/Disable ThermoElectric" ${FEELPP_TOOLBOXES_ENABLE})
option(FEELPP_TOOLBOXES_ENABLE_FLUIDMECHANICS "Enable/Disable FluidMechanics" ${FEELPP_TOOLBOXES_ENABLE})
option(FEELPP_TOOLBOXES_ENABLE_SOLIDMECHANICS "Enable/Disable SolidMechanics" ${FEELPP_TOOLBOXES_ENABLE})
option(FEELPP_TOOLBOXES_ENABLE_FSI "Enable/Disable FSI" ${FEELPP_TOOLBOXES_ENABLE})
option(FEELPP_TOOLBOXES_ENABLE_ADVECTION "Enable/Disable Advection" ${FEELPP_TOOLBOXES_ENABLE})
option(FEELPP_TOOLBOXES_ENABLE_LEVELSET "Enable/Disable LevelSet" ${FEELPP_TOOLBOXES_ENABLE})
option(FEELPP_TOOLBOXES_ENABLE_MULTIFLUID "Enable/Disable MultiFluid" ${FEELPP_TOOLBOXES_ENABLE})
option(FEELPP_TOOLBOXES_ENABLE_HDG "Enable/Disable HDG" ${FEELPP_TOOLBOXES_ENABLE})
option(FEELPP_TOOLBOXES_ENABLE_MAXWELL "Enable/Disable Magnetostatic" ${FEELPP_TOOLBOXES_ENABLE})
#option(FEELPP_ENABLE_PCH_MODELS "Enable precompiled headers for models (pch)" OFF)

set(FEELPP_TOOLBOXES_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(FEELPP_TOOLBOXES_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

include_directories(${CMAKE_SOURCE_DIR}/feelpp)
include_directories(${FEELPP_TOOLBOXES_SOURCE_DIR})
include_directories(${FEELPP_TOOLBOXES_BINARY_DIR})

INCLUDE(CTest)
ENABLE_TESTING()

add_subdirectory( feel/feelmodels )
add_subdirectory( pyfeelpp-toolboxes )

if ( FEELPP_TOOLBOXES_ENABLE_FLUIDMECHANICS )
  add_subdirectory( fluid )
endif()
if ( FEELPP_TOOLBOXES_ENABLE_SOLIDMECHANICS )
  add_subdirectory( solid )
endif()
if ( FEELPP_TOOLBOXES_ENABLE_FSI )
  add_subdirectory( fsi )
endif()
if ( FEELPP_TOOLBOXES_ENABLE_HDG AND ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" ) )
  add_subdirectory( hdg )
endif()
if ( FEELPP_TOOLBOXES_ENABLE_ADVECTION )
  add_subdirectory( advection )
endif()
if( FEELPP_TOOLBOXES_ENABLE_LEVELSET )
  add_subdirectory( levelset )
endif()
if ( FEELPP_TOOLBOXES_ENABLE_MULTIFLUID )
  add_subdirectory( multifluid )
endif()
  # Heat Toolbox
if ( FEELPP_TOOLBOXES_ENABLE_HEAT )
  add_subdirectory( heat )
endif()
if ( FEELPP_TOOLBOXES_ENABLE_HEAT AND FEELPP_TOOLBOXES_ENABLE_FLUIDMECHANICS )
  add_subdirectory( heatfluid )
endif()
if ( FEELPP_TOOLBOXES_ENABLE_THERMOELECTRIC )
  add_subdirectory( thermoelectric )
endif()
if ( FEELPP_TOOLBOXES_ENABLE_MESHALE )
  add_subdirectory( alemesh )
endif()
if ( FEELPP_TOOLBOXES_ENABLE_MAXWELL )
  add_subdirectory( maxwell )
endif()
