/*
    Panopticon - Audio/Graphics/Networking Language
    Copyright (C) 2013 Chad McKinney and Curtis McKinney

    All rights reserved.

    This file is part of Panopticon.

    Panopticon is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Panopticon is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Panopticon.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "include/core/heap.h"
#include "include/core/Memory.h"
#include "include/core/VM.h"
#include "include/Grammar/typeinference.h"

namespace panopticon
{

void startup()
{
    typing::init();
    vm_init();
}

void shutdown()
{
    panopticon::clear_heap();
    panopticon::gc_free_all();
    panopticon::gc_report();
    vm_shutdown();
}

} // panopticon namespace
