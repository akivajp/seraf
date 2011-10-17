#ifndef _FONT_HPP
#define _FONT_HPP

/////////////////////////////////////////////////////////////////////////////
// Name:        lev/font.hpp
// Purpose:     header for font management classes
// Author:      Akiva Miura <akiva.miura@gmail.com>
// Created:     16/08/2010
// Copyright:   (C) 2010-2011 Akiva Miura
// Licence:     MIT License
/////////////////////////////////////////////////////////////////////////////

#include "base.hpp"
#include <luabind/luabind.hpp>

extern "C" {
  int luaopen_lev_font(lua_State *L);
}

namespace lev
{

  class glyph : public base
  {
    protected:
      glyph() { }
//      virtual type_id get_type_id() const { return LEV_TGLYPH; }
      virtual const char *get_type_name() const { return "lev.glyph"; }
    public:
      virtual ~glyph() { }
  };

  class font : public base
  {
    protected:
      font();
    public:
      virtual ~font();
      font* clone();
      std::string get_encoding();
      std::string get_family();
      int get_index();
      int get_pixel_size();
      std::string get_style();
      void *get_rawobj() { return _obj; }
      virtual type_id get_type_id() const { return LEV_TFONT; }
      virtual const char *get_type_name() const { return "lev.font"; }
      static font* load(const std::string &file = "default.ttf", int index = 0);
      static font* load0() { return load(); }
      static font* load1(const std::string &file) { return load(file); }
      bool set_encoding(const std::string &encode);
      bool set_index(int index);
      bool set_pixel_size(int size);
    protected:
      void *_obj;
  };

}

#endif // _FONT_HPP
