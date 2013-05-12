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

#include "core/types.h"
#include "core/Memory.h"

namespace panopticon
{

/*
object::object() : type(NIL)
{
    data.number = 0;
}

object::object(Type type) : type(type)
{
    data = mem_alloc(type).data;
}

object::object(const object& obj)
{
    mem_free(*this);
    data = mem_copy(obj).data;
    type = obj.type;
}

object::~object()
{
    mem_free(*this);
}

object& object::operator=(const object& obj)
{
    mem_free(*this);
    data = mem_copy(obj).data;
    type = obj.type;

    return *this;
}*/

} // panopticon namespace
