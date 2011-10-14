/////////////////////////////////////////////////////////////////////////////
// Name:        src/image.cpp
// Purpose:     source for image handling classes
// Author:      Akiva Miura <akiva.miura@gmail.com>
// Modified by:
// Created:     01/25/2011
// Copyright:   (C) 2010-2011 Akiva Miura
// Licence:     MIT License
/////////////////////////////////////////////////////////////////////////////

#include "prec.h"

#include "lev/image.hpp"

//#include "lev/draw.hpp"
//#include "lev/font.hpp"
#include "lev/util.hpp"
#include "register.hpp"
//#include "resource/levana.xpm"

//#include <boost/shared_array.hpp>
#include <luabind/adopt_policy.hpp>
#include <luabind/luabind.hpp>
//#include <wx/filename.h>
//#include <wx/glcanvas.h>
//#include <wx/graphics.h>
//#include <wx/rawbmp.h>

int luaopen_lev_image(lua_State *L)
{
  using namespace luabind;
  using namespace lev;

  open(L);
  globals(L)["require"]("lev");
//  globals(L)["require"]("lev.font");
  globals(L)["require"]("lev.prim");

  module(L, "lev")
  [
    namespace_("image"),
    namespace_("classes")
    [
      class_<drawable, base>("drawable")
        .def("draw_on", &drawable::draw_on)
        .def("draw_on", &drawable::draw_on1)
        .def("draw_on", &drawable::draw_on3),
      class_<image, drawable>("image")
        .def("blit", &image::blit)
        .def("blit", &image::blit1)
        .def("blit", &image::blit3)
        .def("blit", &image::blit5)
        .def("clear", &image::clear)
        .def("clear", &image::clear0)
        .def("clear", &image::clear_rect)
        .def("clear", &image::clear_rect1)
        .def("draw", &image::blit)
        .def("draw_pixel", &image::draw_pixel)
//        .def("fill_circle", &image::fill_circle)
//        .def("fill_rect", &image::fill_rect)
//        .def("fill_rectangle", &image::fill_rect)
        .def("get_color", &image::get_pixel, adopt(result))
        .def("get_pixel", &image::get_pixel, adopt(result))
        .property("h", &image::get_h)
        .property("height", &image::get_h)
        .def("load", &image::reload)
        .def("reload", &image::reload)
        .def("save", &image::save)
        .def("set_color", &image::set_pixel)
        .def("set_pixel", &image::set_pixel)
        .property("rect",  &image::get_rect)
        .property("sz",  &image::get_size)
        .property("size",  &image::get_size)
//        .def("stroke_circle", &image::stroke_circle)
//        .def("stroke_line", &image::stroke_line)
//        .def("stroke_line", &image::stroke_line6)
//        .def("stroke_rect", &image::stroke_rect)
//        .def("stroke_rectangle", &image::stroke_rect)
        .property("w", &image::get_w)
        .property("width", &image::get_w)
        .scope
        [
//          def("calc_string", &image::calc_string),
//          def("calc_string", &image::calc_string1),
          def("create",  &image::create, adopt(result)),
          def("create",  &image::create2, adopt(result)),
//          def("draw_text_c", &image::draw_text),
//          def("levana_icon", &image::levana_icon),
          def("load",    &image::load, adopt(result)),
//          def("string_c",  &image::string, adopt(result)),
          def("sub_image_c", &image::sub_image, adopt(result))
        ],
        class_<screen, image>("screen")
          .def("flip", &screen::flip)
          .scope
          [
            def("get", &screen::get)
          ]
//      class_<animation, drawable>("animation")
//        .def("add", &animation::add_file)
//        .property("current", &animation::get_current)
//        .scope
//        [
//          def("create", &animation::create, adopt(result)),
//          def("create", &animation::create0, adopt(result))
//        ],
//      class_<transition, drawable>("transition")
//        .property("is_running", &transition::is_running)
//        .def("set_current", &transition::set_current)
//        .def("set_next", &transition::set_next)
//        .scope
//        [
//          def("create", &transition::create, adopt(result)),
//          def("create", &transition::create0, adopt(result))
//        ],
//      class_<layout, drawable>("layout")
//        .def("clear", &layout::clear)
//        .def("clear", &layout::clear0)
//        .property("color", &layout::get_color, &layout::set_color)
//        .def("complete", &layout::complete)
//        .property("font",  &layout::get_font, &layout::set_font)
//        .property("fore",  &layout::get_color, &layout::set_color)
//        .property("is_done", &layout::is_done)
//        .def("on_hover", &layout::on_hover)
//        .def("on_left_click", &layout::on_left_click)
//        .def("reserve_clickable", &layout::reserve_clickable)
//        .def("reserve_clickable", &layout::reserve_clickable_text)
//        .def("reserve_image", &layout::reserve_image)
//        .def("reserve_new_line", &layout::reserve_new_line)
//        .def("reserve_word", &layout::reserve_word)
//        .def("reserve_word", &layout::reserve_word1)
//        .def("set_on_hover", &layout::set_on_hover)
//        .def("show_next", &layout::show_next)
//        .scope
//        [
//          def("create", &layout::create, adopt(result))
//        ]
    ]
  ];
  object lev = globals(L)["lev"];
  object classes = lev["classes"];
  object image = lev["image"];
//  register_to(classes["image"], "draw_text", &image::draw_text_l);
  register_to(classes["image"], "get_sub", &image::sub_image_l);
  register_to(classes["image"], "get_sub_image", &image::sub_image_l);
//  register_to(classes["image"], "string", &image::string_l);
  register_to(classes["image"], "sub", &image::sub_image_l);
  register_to(classes["image"], "sub_image", &image::sub_image_l);

//  image["animation"]   = classes["animation"]["create"];
//  image["calc_string"] = classes["image"]["calc_string"];
//  image["capture"]     = classes["image"]["capture"];
  image["create"]      = classes["image"]["create"];
//  image["layout"]      = classes["layout"]["create"];
//  image["levana_icon"] = classes["image"]["levana_icon"];
  image["load"]        = classes["image"]["load"];
//  image["string"]      = classes["image"]["string"];
//  image["transition"]  = classes["transition"]["create"];

  globals(L)["package"]["loaded"]["lev.image"] = image;
  return 0;
}


namespace lev
{

  static SDL_Surface *cast_image(void *obj) { return (SDL_Surface *)obj; }

  static Uint32 to_color32(SDL_PixelFormat *format, const color &c)
  {
    return SDL_MapRGBA(format, c.get_r(), c.get_g(), c.get_b(), c.get_a());
  }

  static color to_color(SDL_PixelFormat *format, Uint32 code)
  {
    Uint8 r, g, b, a;
    SDL_GetRGBA(code, format, &r, &g, &b, &a);
    return color(r, g, b, a);
  }


  static bool set_pixel_raw(image *img, int x, int y, const color &c)
  {
    SDL_Surface *surf = cast_image(img->get_rawobj());
    if (x < 0 || x >= surf->w || y < 0 || y >= surf->h) { return false; }
    Uint32 rgba = SDL_MapRGBA(surf->format, c.get_r(), c.get_g(), c.get_b(), c.get_a());
    switch(surf->format->BytesPerPixel)
    {
      case 1:
        *((Uint8 *)surf->pixels + y * surf->pitch + x) = rgba;
        break;
      case 2:
        *((Uint16 *)surf->pixels + y * surf->pitch / 2 + x) = rgba;
        break;
      case 3:
        {
          Uint8 *bufp = (Uint8 *)surf->pixels + y * surf->pitch + x * 3;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
          bufp[0] = rgba ;
          bufp[1] = rgba >> 8;
          bufp[2] = rgba >> 16;
#else
          bufp[2] = rgba;
          bufp[1] = rgba >> 8;
          bufp[0] = rgba >> 16;
#endif
          break;
        }
      case 4:
        *((Uint32 *)surf->pixels + y * surf->pitch / 4 + x) = rgba;
        break;
      default:
        return false;
    }
    return true;
  }

  static color* get_pixel_raw(image *img, int x, int y)
  {
    Uint32 code = 0;
    SDL_Surface *surf = cast_image(img->get_rawobj());
    if (x < 0 || x >= surf->w || y < 0 || y >= surf->h) { return NULL; }
    switch (surf->format->BytesPerPixel)
    {
      case 1:
        code = *((Uint8 *)surf->pixels + y * surf->pitch + x);
        break;
      case 2:
        code = *((Uint16 *)surf->pixels + y * surf->pitch / 2 + x);
        break;
      case 3:
        {
          Uint8 *bufp = (Uint8 *)surf->pixels + y * surf->pitch + x * 3;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
          code = bufp[0] | (bufp[1] << 8) | (bufp[2] << 16);
#else
          code = bufp[2] | (bufp[1] << 8) | (bufp[0] << 16);
#endif
          break;
        }
      case 4:
        code = *((Uint32 *)surf->pixels + y * surf->pitch / 4 + x);
        break;
      default:
        return NULL;
    }

    Uint8 r, g, b, a;
    SDL_GetRGBA(code, surf->format, &r, &g, &b, &a);
    return color::create(r, g, b, a);
  }

  static bool draw_pixel_raw(image *img, int x, int y, const color &c)
  {
    boost::shared_ptr<color> src(get_pixel_raw(img, x, y));
    if (! src) { return false; }
    if (src->get_a() == 0)
    {
      return set_pixel_raw(img, x, y, c);
    }
    else
    {
      double alpha_norm = c.get_a() / 255.0;
      double base_alpha = (1 - alpha_norm) * src->get_a() / 255.0;
      unsigned char r, g, b, a;
      a = 255 * (alpha_norm + base_alpha);
      if (a > 0)
      {
        double fix = 255.0 / a;
        r = (src->get_r() * base_alpha + c.get_r() * alpha_norm) * fix;
        g = (src->get_g() * base_alpha + c.get_g() * alpha_norm) * fix;
        b = (src->get_b() * base_alpha + c.get_b() * alpha_norm) * fix;
        return set_pixel_raw(img, x, y, color(r, g, b, a));
      }
    }
    return false;
  }

  class surface_locker
  {
    public:
      surface_locker(SDL_Surface *surf) : surf_hold(NULL), result(false)
      {
        if (SDL_MUSTLOCK(surf))
        {
          if (SDL_LockSurface(surf) == 0)
          {
            surf_hold = surf;
            result = true;
          }
        }
        else { result = true; }
      }

      ~surface_locker()
      {
        if (surf_hold) { SDL_UnlockSurface(surf_hold); }
      }

      bool success() { return result; }

    private:
      SDL_Surface *surf_hold;
      bool result;
  };

  image::image() : drawable(), _obj(NULL) { }

  image::~image()
  {
    if (_obj)
    {
      SDL_FreeSurface(cast_image(_obj));
      _obj = NULL;
    }
  }

  bool image::blit(int src_x, int src_y, int w, int h, image *dst, int dst_x, int dst_y)
  {
    if (dst == NULL) { return false; }

    SDL_Surface *surf_src = cast_image(_obj);
    SDL_Surface *surf_dst = cast_image(dst->_obj);
    SDL_Rect rect_src;
    rect_src.x = src_x;
    rect_src.y = src_y;
    rect_src.w = w;
    rect_src.h = h;
    SDL_Rect rect_dst;
    rect_dst.x = dst_x;
    rect_dst.y = dst_y;
    if (SDL_BlitSurface(surf_src, &rect_src, surf_dst, &rect_dst) == 0) { return true; }
    else { return false; }
  }

  bool image::blit3(image *dst, int dst_x, int dst_y)
  {
    if (dst == NULL) { return false; }

    SDL_Surface *surf_src = cast_image(_obj);
    SDL_Surface *surf_dst = cast_image(dst->_obj);
    SDL_Rect rect_dst;
    rect_dst.x = dst_x;
    rect_dst.y = dst_y;
    if (SDL_BlitSurface(surf_src, NULL, surf_dst, &rect_dst) == 0) { return true; }
    else { return false; }
  }


//  size image::calc_string(const std::string &str, font *f)
//  {
//    wxMemoryDC mdc;
//    if (f)
//    {
//      wxFont *font = (wxFont *)f->get_rawobj();
//      mdc.SetFont(*font);
//    }
//    else { mdc.SetFont(*wxNORMAL_FONT); }
//    wxSize sz = mdc.GetTextExtent(wxString(str.c_str(), wxConvUTF8));
//    return size(sz.GetWidth(), sz.GetHeight());
//  }

  bool image::clear(const color &c)
  {
    SDL_Surface *surf = cast_image(_obj);
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = surf->w;
    rect.h = surf->h;
    if (SDL_FillRect(surf, &rect, to_color32(surf->format, c)) == 0) { return true; }
    else { return false; }
  }

  bool image::clear_rect(const rect &r, const color &c)
  {
    SDL_Surface *surf = cast_image(_obj);
    SDL_Rect rect_src;
    rect_src.x = r.get_x();
    rect_src.y = r.get_y();
    rect_src.w = r.get_w();
    rect_src.h = r.get_h();
    if (SDL_FillRect(surf, &rect_src, to_color32(surf->format, c)) == 0) { return true; }
    else { return false; }
  }

  image* image::clone()
  {
    image* img = NULL;
    SDL_Surface *surf = cast_image(_obj);
    try {
      img = new image;
      img->_obj = SDL_DisplayFormatAlpha(surf);
      if (! img->_obj) { throw -1; }
      return img;
    }
    catch (...) {
      delete img;
      return NULL;
    }
  }

  image* image::create(int width, int height, int depth)
  {
    image *img = NULL;
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
    try {
      img = new image;
      img->_obj = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA,
                                       width, height, depth,
                                       rmask, gmask, bmask, amask);
      if (! img->_obj) { throw -1; }
      return img;
    }
    catch (...) {
      delete img;
      return NULL;
    }
  }

  bool image::draw_on(image *dst, int x, int y, unsigned char alpha)
  {
    SDL_Surface *surf_src = cast_image(_obj);
    SDL_Surface *surf_dst = cast_image(dst->_obj);
    bool result = false;

    SDL_Rect rect_dst;
    rect_dst.x = x;
    rect_dst.y = y;
    if (alpha == 255)
    {
      if (SDL_BlitSurface(surf_src, NULL, surf_dst, &rect_dst) == 0) { result = true; }
    }
    else
    {
      SDL_SetAlpha(surf_src, SDL_SRCALPHA | SDL_RLEACCEL, alpha);
      if (SDL_BlitSurface(surf_src, NULL, surf_dst, &rect_dst) == 0) { result = true; }
      SDL_SetAlpha(surf_src, SDL_SRCALPHA | SDL_RLEACCEL, 255);
    }
    return result;
  }

  bool image::draw_pixel(int x, int y, const color &c)
  {
    surface_locker lock(cast_image(_obj));
    if (! lock.success()) { return false; }
    return draw_pixel_raw(this, x, y, c);
  }
//
//  bool image::draw_text(const std::string &text, font *f, color *fg, color *bg, int x, int y)
//  {
//    try {
//      boost::shared_ptr<image> txt(image::string(text, f, fg, bg));
//      if (txt.get() == NULL) { throw -1; }
//      return blit(txt.get(), x, y);
//    }
//    catch (...) {
//      return false;
//    }
//  }
//
//  int image::draw_text_l(lua_State *L)
//  {
//    using namespace luabind;
//    int x = 0, y = 0;
//
//    try {
//      luaL_checktype(L, 1, LUA_TUSERDATA);
//      object img(from_stack(L, 1));
//      object t = util::get_merged(L, 2, -1);
//
//      object txt_img = globals(L)["lev"]["classes"]["image"]["string"](t);
//
//      if (t["x"]) { x = object_cast<int>(t["x"]); }
//      else if (t["lua.number1"]) { x = object_cast<int>(t["lua.number1"]); }
//
//      if (t["y"]) { y = object_cast<int>(t["y"]); }
//      else if (t["lua.number2"]) { y = object_cast<int>(t["lua.number2"]); }
//
//      object res = img["blit"](img, txt_img, x, y);
//      res.push(L);
//      return 1;
//    }
//    catch (...) {
//      lua_pushnil(L);
//      return 1;
//    }
//  }
//
  int image::get_h() const
  {
    return cast_image(_obj)->h;
  }
//
//  bool image::fill_circle(int x, int y, int radius, color *filling)
//  {
//    wxBitmap tmp(get_w(), get_h(), 32);
//    try {
//      wxMemoryDC mdc(tmp);
//      mdc.SetPen(wxColour(255, 255, 255, 255));
//      mdc.SetBrush(wxColour(255, 255, 255, 255));
//      mdc.SetBackground(wxColour(0, 0, 0, 255));
//      mdc.Clear();
//      mdc.DrawCircle(x, y, radius);
//    }
//    catch (...) {
//      return false;
//    }
//    return image_draw_mask(this, &tmp, filling);
//  }
//
//  bool image::fill_rect(int x, int y, int w, int h, color *filling)
//  {
//#ifdef __WXGTK__
//    wxBitmap tmp(get_w(), get_h(), 32);
//
//    try {
//      wxMemoryDC mdc(tmp);
//      mdc.SetPen(wxColour(255, 255, 255, 255));
//      mdc.SetBrush(wxColour(255, 255, 255, 255));
//      mdc.SetBackground(wxColour(0, 0, 0, 255));
//      mdc.Clear();
//      mdc.DrawRectangle(x, y, w, h);
//      return image_draw_mask(this, &tmp, filling);
//    }
//    catch (...) {
//      return false;
//    }
//#else
//    try {
//      wxMemoryDC mdc(*cast_image(_obj));
//      wxGCDC gdc(mdc);
//      if (filling)
//      {
//        gdc.SetPen(wxColour(to_wxcolor(*filling)));
//        gdc.SetBrush(wxColour(to_wxcolor(*filling)));
//      }
//      gdc.DrawRectangle(x, y, w, h);
//      return true;
//    }
//    catch (...) {
//      return false;
//    }
//#endif
//  }
//
//
  color* image::get_pixel(int x, int y)
  {
    surface_locker lock(cast_image(_obj));
    if (! lock.success()) { throw -1; }
    return get_pixel_raw(this, x, y);
  }

  const rect image::get_rect() const
  {
    return rect(0, 0, get_w(), get_h());
  }

  const size image::get_size() const
  {
    return size(get_w(), get_h());
  }

  int image::get_w() const
  {
    return cast_image(_obj)->w;
  }

//  image* image::levana_icon()
//  {
//    static image *img = NULL;
//    wxBitmap *obj = NULL;
//
//    if (img) { return img; }
//    try {
//      img = new image;
//      img->_obj = obj = new wxBitmap(levana_xpm);
//      img->_status = new myImageStatus;
//      return img;
//    }
//    catch (...) {
//      delete img;
//      return NULL;
//    }
//  }

  image* image::load(const std::string &filename)
  {
    image *img = NULL;
    try {
      img = new image;
      img->_obj = SDL_LoadBMP(filename.c_str());
      if (! img->_obj) { throw -1; }
      return img;
    }
    catch (...) {
      delete img;
      return NULL;
    }
  }

  bool image::reload(const std::string &filename)
  {
    SDL_Surface *surf = SDL_LoadBMP(filename.c_str());
    if (! surf) { return false; }
    delete cast_image(_obj);
    _obj = surf;
    return true;
  }

  bool image::save(const std::string &filename) const
  {
    if (SDL_SaveBMP(cast_image(_obj), filename.c_str()) == 0) { return true; }
    else { return false; }
  }

  bool image::set_pixel(int x, int y, const color &c)
  {
    surface_locker lock(cast_image(_obj));
    if (! lock.success()) { return false; }
    return set_pixel_raw(this, x, y, c);
  }
//
//
//  image* image::string(const std::string &str, font *f, color *fore, color *back)
//  {
//    image *img = NULL;
//    if (str.empty()) { return NULL; }
//
//#ifdef __WXMSW__
//    try {
//      wxString s(str.c_str(), wxConvUTF8);
//      if (s.empty()) { s = wxString(str.c_str(), wxConvLibc); }
//      wxMemoryDC mdc;
//      wxGCDC gdc(mdc);
//      if (f)
//      {
//        wxFont *ft = (wxFont *)f->get_rawobj();
//        gdc.SetFont(*ft);
//      }
//      else { gdc.SetFont(*wxNORMAL_FONT); }
//      wxSize sz = gdc.GetTextExtent(s);
//      img = image::create(sz.GetWidth(), sz.GetHeight());
//      if (! img) { throw -1; }
//      mdc.SelectObject(*cast_image(img->_obj));
//      if (fore) { gdc.SetTextForeground(to_wxcolor(*fore)); }
//      gdc.DrawText(s, 0, 0);
//      return img;
//    }
//    catch (...) {
//      delete img;
//      return NULL;
//    }
//#else
//    try {
//      wxMemoryDC mdc;
//      wxString s(str.c_str(), wxConvUTF8);
//      if (s.empty()) { s = wxString(str.c_str(), wxConvLibc); }
//      if (f)
//      {
//        wxFont *font = (wxFont *)f->get_rawobj();
//        mdc.SetFont(*font);
//      }
//      else { mdc.SetFont(*wxNORMAL_FONT); }
//      wxSize sz = mdc.GetTextExtent(s);
//      if (sz.GetWidth() == 0 || sz.GetHeight() == 0) { throw -1; }
//
//      img = image::create(sz.GetWidth(), sz.GetHeight());
//      if (img == NULL) { throw -2; }
//      mdc.SelectObject(*cast_image(img->get_rawobj()));
//      mdc.SetBrush(wxColour(0, 0, 0, 255));
//      mdc.SetTextForeground(wxColour(255, 255, 255, 255));
//      mdc.DrawText(s, 0, 0);
//
//      wxAlphaPixelData data(*cast_image(img->_obj));
//      data.UseAlpha();
//      wxAlphaPixelData::Iterator p(data), rawStart;
//      for (int y = 0 ; y < sz.GetHeight() ; y++)
//      {
//        rawStart = p;
//        for (int x = 0 ; x < sz.GetWidth() ; x++)
//        {
//          double ave = ((double)p.Red() + (double)p.Green() + (double)p.Blue()) / 3.0;
//          double alpha_norm = ave / 255.0;
//          if (fore)
//          {
//            if (back && back->get_a() > 0)
//            {
//              alpha_norm = alpha_norm * fore->get_a() / 255.0;
//              double base_alpha = (1 - alpha_norm) * back->get_a() / 255.0;
//              p.Alpha() = 255 * (alpha_norm + base_alpha);
//              if (p.Alpha() > 0)
//              {
//                double fix = 255.0 / p.Alpha();
//                p.Red()   = (back->get_r() * base_alpha + fore->get_r() * alpha_norm) * fix;
//                p.Green() = (back->get_g() * base_alpha + fore->get_g() * alpha_norm) * fix;
//                p.Blue()  = (back->get_b() * base_alpha + fore->get_b() * alpha_norm) * fix;
//              }
//            }
//            else // if (!back)
//            {
//              p.Red()   = fore->get_r();
//              p.Green() = fore->get_g();
//              p.Blue()  = fore->get_b();
//              p.Alpha() = alpha_norm * fore->get_a();
//            }
//          }
//          else // if (!fore)
//          {
//            if (back)
//            {
//              p.Red()   = back->get_r() * (1 - alpha_norm);
//              p.Green() = back->get_g() * (1 - alpha_norm);
//              p.Blue()  = back->get_b() * (1 - alpha_norm);
//              p.Alpha() = back->get_a() * (1 - alpha_norm) + 255 * alpha_norm;
//            }
//            else // if (!back)
//            {
//              p.Red()   = 0;
//              p.Green() = 0;
//              p.Blue()  = 0;
//              p.Alpha() = ave;
//            }
//          }
//          ++p;
//        }
//        p = rawStart;
//        p.OffsetY(data, 1);
//      }
//      return img;
//    }
//    catch (...) {
//      delete img;
//      return NULL;
//    }
//#endif
//  }
//
//  int image::string_l(lua_State *L)
//  {
//    using namespace luabind;
//    const char *str = NULL;
//    object font, fore, back;
//
//    object t = util::get_merged(L, 1, -1);
//
//    if (t["lua.string1"]) { str = object_cast<const char *>(t["lua.string1"]); }
//    else if (t["lev.mb_string1"]) { str = object_cast<const char *>(t["lev.mb_string1"]["str"]); }
//    else if (t["text"]) { str = object_cast<const char *>(t["text"]); }
//    else if (t["t"]) { str = object_cast<const char *>(t["t"]); }
//    else if (t["string"]) { str = object_cast<const char *>(t["string"]); }
//    else if (t["str"]) { str = object_cast<const char *>(t["str"]); }
//
//    if (not str)
//    {
//      luaL_error(L, "text (string) is not specified!\n");
//      return 0;
//    }
//
//    if (t["lev.font"]) { font = t["lev.font"]; }
//    else if (t["font"]) { font = t["font"]; }
//    else if (t["f"]) { font = t["f"]; }
//
//    if (t["lev.prim.color1"]) { fore = t["lev.prim.color1"]; }
//    else if (t["fg_color"]) { fore = t["fg_color"]; }
//    else if (t["fg"]) { fore = t["fg"]; }
//    else if (t["fore"]) { fore = t["fore"]; }
//    else if (t["f"]) { fore = t["f"]; }
//    else if (t["color"]) { fore = t["color"]; }
//    else if (t["c"]) { fore = t["c"]; }
//
//    if (t["lev.prim.color2"]) { back = t["lev.prim.color2"]; }
//    else if (t["bg_color"]) { back = t["bg_color"]; }
//    else if (t["bg"]) { back = t["bg"]; }
//    else if (t["back"]) { back = t["back"]; }
//    else if (t["b"]) { back = t["b"]; }
//
//    object o = globals(L)["lev"]["classes"]["image"]["string_c"](str, font, fore, back);
//    o.push(L);
//    return 1;
//  }
//
//  bool image::stroke_circle(int x, int y, int radius, color *border, int width)
//  {
//    wxBitmap tmp(get_w(), get_h(), 32);
//    try {
//      wxMemoryDC mdc(tmp);
//      mdc.SetPen(wxPen(wxColour(255, 255, 255, 255), width));
//      mdc.SetBrush(wxColour(0, 0, 0, 255));
//      mdc.SetBackground(wxColour(0, 0, 0, 255));
//      mdc.Clear();
//      mdc.DrawCircle(x, y, radius);
//    }
//    catch (...) {
//      return false;
//    }
//    return image_draw_mask(this, &tmp, border);
//  }
//
//  bool image::stroke_line(int x1, int y1, int x2, int y2, color *border, int width,
//                          const std::string &style)
//  {
//    wxBitmap tmp(get_w(), get_h(), 32);
//    try {
//      wxMemoryDC mdc(tmp);
//      if (style == "dot")
//      {
//        mdc.SetPen(wxPen(wxColour(255, 255, 255, 255), width, wxDOT));
//      }
//      else
//      {
//        mdc.SetPen(wxPen(wxColour(255, 255, 255, 255), width));
//      }
//      mdc.SetBrush(wxColour(0, 0, 0, 255));
//      mdc.SetBackground(wxColour(0, 0, 0, 255));
//      mdc.Clear();
//      mdc.DrawLine(x1, y1, x2, y2);
//    }
//    catch (...) {
//      return false;
//    }
//    return image_draw_mask(this, &tmp, border);
//  }
//
//  bool image::stroke_rect(int x, int y, int w, int h, color *border, int width)
//  {
//    wxBitmap tmp(get_w(), get_h(), 32);
//    try {
//      wxMemoryDC mdc(tmp);
//      mdc.SetPen(wxPen(wxColour(255, 255, 255, 255), width));
//      mdc.SetBrush(wxColour(0, 0, 0, 255));
//      mdc.SetBackground(wxColour(0, 0, 0, 255));
//      mdc.Clear();
//      mdc.DrawRectangle(x, y, w, h);
//    }
//    catch (...) {
//      return false;
//    }
//    return image_draw_mask(this, &tmp, border);
//  }
//
  image* image::sub_image(int x, int y, int w, int h)
  {
    image* img = NULL;
    try {
      img = image::create(w, h, 32);
      if (! img) { throw -1; }
      blit(x, y, w, h, img, 0, 0);
      return img;
    }
    catch (...) {
      delete img;
      return NULL;
    }
  }

  int image::sub_image_l(lua_State *L)
  {
    using namespace luabind;
    int x = 0, y = 0, w = -1, h = -1;

    luaL_checktype(L, 1, LUA_TUSERDATA);
    image *img = object_cast<image *>(object(from_stack(L, 1)));
    if (img == NULL) { return 0; }
    object t = util::get_merged(L, 2, -1);

    if (t["x"]) { x = object_cast<int>(t["x"]); }
    else if (t["lua.number1"]) { x = object_cast<int>(t["lua.number1"]); }
    if (x < 0) { x = 0; }

    if (t["y"]) { y = object_cast<int>(t["y"]); }
    else if (t["lua.number2"]) { y = object_cast<int>(t["lua.number2"]); }
    if (y < 0) { y = 0; }

    if (t["w"]) { w = object_cast<int>(t["w"]); }
    else if (t["lua.number3"]) { w = object_cast<int>(t["lua.number3"]); }
    if (w < 0) { w = img->get_w() - x; }

    if (t["h"]) { h = object_cast<int>(t["h"]); }
    else if (t["lua.number4"]) { h = object_cast<int>(t["lua.number4"]); }
    if (h < 0) { h = img->get_h() - y; }

    object o = globals(L)["lev"]["classes"]["image"]["sub_image_c"](img, x, y, w, h);
    o.push(L);
    return 1;
  }

  bool image::swap(image *img)
  {
    if (! img) { return false; }
    // swap the images
    void *tmp  = this->_obj;
    this->_obj = img->_obj;
    img->_obj  = tmp;
    return true;
  }


  screen::screen() : image() { }

  screen::~screen()
  {
    // not removing by SDL_FreeSurface !
    _obj = NULL;
  }

  bool screen::flip()
  {
    SDL_Surface *screen = SDL_GetVideoSurface();
    if (SDL_Flip(screen) == 0) { return true; }
    else { return false; }
  }

  screen* screen::get()
  {
    static screen scr;
    if (scr._obj) { return &scr; }
    scr._obj = SDL_GetVideoSurface();
    if (! scr._obj) { return NULL; }
    return &scr;
  }

  screen* screen::set_mode(int width, int height, int depth)
  {
    SDL_SetVideoMode(width, height, depth, SDL_DOUBLEBUF);
    return get();
  }

  /*
  class myAnimation
  {
    public:

      myAnimation(bool repeating = true) : imgs(), repeating(repeating)
      {
        sw.Start(0);
      }

      ~myAnimation() { }

      bool AddFile(const std::string &filename, int duration)
      {
        if (duration <= 0) { return false; }
        try {
          boost::shared_ptr<image> img(image::load(filename));
          if (! img) { throw -1; }
          imgs.push_back(img);
          durations.push_back(duration);
          return true;
        }
        catch (...) {
          return false;
        }
      }

      bool CompileAll(canvas *cv, bool force)
      {
        for (int i = 0; i < imgs.size(); i++)
        {
          cv->compile(imgs[i].get(), force);
        }
        return true;
      }

      image* GetCurrent()
      {
        long now = sw.Time();
        long total = 0;
        if (imgs.size() == 0) { return NULL; }
        for (int i = 0; i < durations.size(); i++)
        {
          if (total <= now && now < total + durations[i])
          {
            return imgs[i].get();
          }
          total += durations[i];
        }
        if (! repeating) { return imgs[imgs.size() - 1].get(); }
        sw.Start(sw.Time() - total);
        return GetCurrent();
      }

      bool TexturizeAll(canvas *cv, bool force)
      {
        for (int i = 0; i < imgs.size(); i++)
        {
          cv->texturize(imgs[i].get(), force);
        }
        return true;
      }

      bool repeating;
      wxStopWatch sw;
      std::vector<boost::shared_ptr<image> > imgs;
      std::vector<int> durations;
  };
  static myAnimation* cast_anim(void *obj) { return (myAnimation *)obj; }

  animation::animation()
    : drawable(), _obj(NULL)
  { }

  animation::~animation()
  {
    if (_obj) { delete cast_anim(_obj); }
  }

  bool animation::add_file(const std::string &filename, int duration)
  {
    return cast_anim(_obj)->AddFile(filename, duration);
  }

  bool animation::compile(canvas *cv, bool force)
  {
    return cast_anim(_obj)->CompileAll(cv, force);
  }

  image* animation::get_current()
  {
    return cast_anim(_obj)->GetCurrent();
  }

  animation* animation::create(bool repeating)
  {
    animation* anim = NULL;
    try {
      anim = new animation;
      anim->_obj = new myAnimation(repeating);
      return anim;
    }
    catch (...) {
      delete anim;
      return NULL;
    }
  }

  bool animation::texturize(canvas *cv, bool force)
  {
    return cast_anim(_obj)->TexturizeAll(cv, force);
  }


  class myTransition
  {
    public:

      enum transition_type
      {
        LEV_TRAN_NONE = 0,
        LEV_TRAN_FADE,
        LEV_TRAN_FADE_OUT,
      };

      myTransition(luabind::object img)
       : imgs()
      {
        sw.Start();
        if (! img) { imgs.push_back(luabind::object()); }
        else if (luabind::type(img) == LUA_TSTRING)
        {
          luabind::object data = globals(img.interpreter())["lev"]["image"]["load"](img);
          imgs.push_back(data);
        }
        else if (base::is_type_of(img, base::LEV_TFILE_PATH))
        {
          luabind::object data = globals(img.interpreter())["lev"]["image"]["load"](img["full"]);
          imgs.push_back(data);
        }
        else if (base::is_type_of(img, base::LEV_TDRAWABLE, base::LEV_TDRAWABLE_END)) { imgs.push_back(img); }
        else { imgs.push_back(luabind::object()); }
      }

      ~myTransition() { }

      bool DrawOn(canvas *cv, int x, int y, unsigned char alpha)
      {
        double grad = 1.0;
        if (durations.size() >= 1 && durations[0] > 0)
        {
          grad = ((double)sw.Time()) / durations[0];
          if (grad > 1.0) { grad = 1.0; }
        }

        if (imgs.size() == 0) { return false; }
        if (imgs[0])
        {
          if (types.size() >= 1 && types[0] == LEV_TRAN_FADE_OUT)
          {
            imgs[0]["draw_on"](imgs[0], cv, x, y, 255 - (int)(alpha * grad));
          }
          else { imgs[0]["draw_on"](imgs[0], cv, x, y, alpha); }
        }

        if (imgs.size() == 1) { return true; }
        if (imgs[1])
        {
          if (types[0] == LEV_TRAN_FADE)
          {
            imgs[1]["draw_on"](imgs[1], cv, x, y, alpha * grad);
          }
        }

        if (sw.Time() >= durations[0])
        {
          sw.Start(sw.Time() - durations[0]);
          imgs.erase(imgs.begin());
          durations.erase(durations.begin());
          types.erase(types.begin());
        }
        return true;
      }

      bool SetCurrent(luabind::object img)
      {
        imgs.resize(0);
        durations.resize(0);
        if (! img) { imgs.push_back(luabind::object()); }
        else if (luabind::type(img) == LUA_TSTRING)
        {
          luabind::object data = globals(img.interpreter())["lev"]["image"]["load"](img);
          imgs.push_back(data);
        }
        else if (base::is_type_of(img, base::LEV_TFILE_PATH))
        {
          luabind::object data = globals(img.interpreter())["lev"]["image"]["load"](img["full"]);
          imgs.push_back(data);
        }
        else if (base::is_type_of(img, base::LEV_TDRAWABLE, base::LEV_TDRAWABLE_END)) { imgs.push_back(img); }
        else { imgs.push_back(luabind::object()); }
      }

      bool SetNext(luabind::object img, int duration, const std::string &type)
      {
        if (duration < 0) { return false; }
        if (! img) { imgs.push_back(luabind::object()); }
        else if (luabind::type(img) == LUA_TSTRING)
        {
          luabind::object data = globals(img.interpreter())["lev"]["image"]["load"](img);
          imgs.push_back(data);
        }
        else if (base::is_type_of(img, base::LEV_TFILE_PATH))
        {
          luabind::object data = globals(img.interpreter())["lev"]["image"]["load"](img["full"]);
          imgs.push_back(data);
        }
        else if (base::is_type_of(img, base::LEV_TDRAWABLE, base::LEV_TDRAWABLE_END)) { imgs.push_back(img); }
        else { imgs.push_back(luabind::object()); }

        durations.push_back(duration);

        if (type == "fade") { types.push_back(LEV_TRAN_FADE); }
        else if (type == "fade_out") { types.push_back(LEV_TRAN_FADE_OUT); }
        else { types.push_back(LEV_TRAN_FADE); }

        return false;
      }

      bool TexturizeAll(canvas *cv, bool force)
      {
        for (int i = 0; i < imgs.size(); i++)
        {
          if (base::is_type_of(imgs[i], base::LEV_TDRAWABLE, base::LEV_TDRAWABLE_END))
          {
            imgs[i]["texturize"](imgs[i], cv, force);
          }
        }
        return true;
      }

      std::vector<luabind::object> imgs;
      std::vector<long> durations;
      std::vector<transition_type> types;
      wxStopWatch sw;
  };
  static myTransition* cast_tran(void *obj) { return (myTransition *)obj; }

  transition::transition() : drawable(), _obj(NULL) { }

  transition::~transition()
  {
    if (_obj) { delete cast_tran(_obj); }
  }

  transition* transition::create(luabind::object img)
  {
    transition* tran = NULL;
    try {
      tran = new transition;
      tran->_obj = new myTransition(img);
      return tran;
    }
    catch (...) {
      delete tran;
      return NULL;
    }
  }

  bool transition::draw_on(canvas *cv, int x, int y, unsigned char alpha)
  {
    return cast_tran(_obj)->DrawOn(cv, x, y, alpha);
  }

  bool transition::is_running()
  {
    if (cast_tran(_obj)->imgs.size() <= 1) { return false; }
    else { return true; }
  }

  bool transition::set_current(luabind::object current)
  {
    return cast_tran(_obj)->SetCurrent(current);
  }

  bool transition::set_next(luabind::object next, int duration, const std::string &type)
  {
    return cast_tran(_obj)->SetNext(next, duration, type);
  }

  bool transition::texturize(canvas *cv, bool force)
  {
    return cast_tran(_obj)->TexturizeAll(cv, force);
  }


  class myLayout
  {
    public:

      myLayout(int width_stop = -1)
        : h(-1), w(width_stop), current_x(0), last_index(0), font_obj(),
          index_to_col(), index_to_row(), log(), rows()
      {
        font_obj = globals(application::get_app()->getL())["lev"]["font"]["load"]();
        font_obj["size"] = 24;
        color_obj = globals(application::get_app()->getL())["lev"]["prim"]["color"](0, 0, 0);
        hover_fg_color_obj = globals(application::get_app()->getL())["lev"]["prim"]["color"](255, 0, 0);
        hover_bg_color_obj = globals(application::get_app()->getL())["lev"]["prim"]["color"](0, 0, 0, 0);

        rows.push_back(std::vector<boost::shared_ptr<image> >());
      }

      int CalcMaxWidth()
      {
        int width = 0;
        for (int i = 0; i < rows.size(); i++)
        {
          int current = CalcRowWidth(rows[i]);
          if (current > width) { width = current; }
        }
        return width;
      }

      int CalcRowHeight(const std::vector<boost::shared_ptr<image> > &row)
      {
        int height = 0;
        for (int i = 0; i < row.size(); i++)
        {
          if (row[i]->get_h() > height) { height = row[i]->get_h(); }
        }
        return height;
      }

      int CalcRowWidth(const std::vector<boost::shared_ptr<image> > &row)
      {
        int width = 0;
        for (int i = 0; i < row.size(); i++)
        {
          width += row[i]->get_w();
        }
        return width;
      }

      int CalcTotalHeight()
      {
        int height = 0;
        for (int i = 0; i < rows.size(); i++)
        {
          height += CalcRowHeight(rows[i]);
        }
        return height;
      }

      bool Clear()
      {
        current_x = 0;
        last_index = 0;
        index_to_col.clear();
        index_to_row.clear();
        log.clear();
        rows.clear();

        actives.clear();
        clickable_areas.clear();
        coordinates.clear();
        hover_funcs.clear();
        hover_imgs.clear();
        lclick_funcs.clear();
        name_to_index.clear();

        rows.push_back(std::vector<boost::shared_ptr<image> >());
        return true;
      }

      bool Complete()
      {
        for (; last_index < log.size(); last_index++)
        {
          ShowIndex(last_index);
        }
        return true;
      }


      bool DrawOn(canvas *cv, int x, int y, unsigned char alpha)
      {
        for (int i = 0; i < actives.size(); i++)
        {
          if (actives[i])
          {
            const vector &vec = coordinates[i];
            actives[i]->draw_on(cv, x + vec.get_x(), y + vec.get_y(), alpha);
          }
        }
        return true;
      }

      bool OnHover(int x, int y)
      {
        using namespace luabind;

        for (int i = 0; i < last_index; i++)
        {
          std::map<int, rect>::iterator found = clickable_areas.find(i);
          if (found == clickable_areas.end()) { continue; }
          const rect &r = found->second;
          if (r.include(x, y))
          {
            if (hover_imgs.find(i) != hover_imgs.end())
            {
              actives[i] = hover_imgs[i];
            }
            if (hover_funcs.find(i) != hover_funcs.end())
            {
              if (hover_funcs[i] && type(hover_funcs[i]) == LUA_TFUNCTION)
              {
                hover_funcs[i](x, y);
              }
            }
          }
          else
          {
            // (x, y) isn't in the rect
            ShowIndex(i);
            continue;
          }
        }
        return true;
      }

      bool OnLeftClick(int x, int y)
      {
        using namespace luabind;

        for (int i = 0; i < last_index; i++)
        {
          std::map<int, rect>::iterator found = clickable_areas.find(i);
          if (found == clickable_areas.end()) { continue; }
          const rect &r = found->second;
          if (r.include(x, y))
          {
            if (lclick_funcs.find(i) != lclick_funcs.end())
            {
              if (lclick_funcs[i] && type(lclick_funcs[i]) == LUA_TFUNCTION)
              {
                lclick_funcs[i](x, y);
              }
            }
            return true;
          }
        }
        return false;
      }

      bool ReserveClickable(const std::string &name,
                            boost::shared_ptr<image> normal,
                            boost::shared_ptr<image> hover,
                            luabind::object lclick_func)
      {
        try {
          if (! normal) { throw -1; }
          if (! hover) { throw -1; }
          if (w >= 0 && current_x + normal->get_w() > w)
          {
            rows.push_back(std::vector<boost::shared_ptr<image> >());
            current_x = 0;
          }
          int index = log.size();
          current_x += normal->get_w();
          index_to_col.push_back(rows[rows.size() - 1].size());
          index_to_row.push_back(rows.size() - 1);
          log.push_back(name);
          rows[rows.size() - 1].push_back(normal);

          hover_imgs[index] = hover;
          lclick_funcs[index] = lclick_func;
          name_to_index[name] = index;
          return true;
        }
        catch (...) {
          return false;
        }
      }

      bool ReserveClickableText(const std::string &name,
                                const std::string &text,
                                luabind::object lclick_func)
      {
        if (text.empty()) { return false; }
        try {
          font *f = object_cast<font *>(font_obj);
          color *c = object_cast<color *>(color_obj);
          color *hover_bg = object_cast<color *>(hover_bg_color_obj);
          color *hover_fg = object_cast<color *>(hover_fg_color_obj);
          boost::shared_ptr<image> img;
          boost::shared_ptr<image> hover_img;

          img.reset(image::string(text, f, c));
          img->stroke_line(0, img->get_h() - 1,
                           img->get_w() - 1, img->get_h() - 1, c, 1, "dot");
          hover_img.reset(image::string(text, f, hover_fg, hover_bg));
          return ReserveClickable(name, img, hover_img, lclick_func);
        }
        catch (...) {
          return false;
        }
      }

      bool ReserveImage(const std::string &name, boost::shared_ptr<image> img)
      {
        try {
          if (! img) { throw -1; }
          if (w >= 0 && current_x + img->get_w() > w)
          {
            rows.push_back(std::vector<boost::shared_ptr<image> >());
            current_x = 0;
          }
          current_x += img->get_w();
          index_to_col.push_back(rows[rows.size() - 1].size());
          index_to_row.push_back(rows.size() - 1);
          log.push_back(name);
          rows[rows.size() - 1].push_back(img);
          return true;
        }
        catch (...) {
          return false;
        }
      }

      bool ReserveNewLine()
      {
        font *f = object_cast<font *>(font_obj);
        boost::shared_ptr<image> new_line(image::create(1, f->get_point_size()));
        if (! new_line) { return false; }
        ReserveImage("space", new_line);
        rows.push_back(std::vector<boost::shared_ptr<image> >());
        current_x = 0;
      }

      bool ReserveWord(const std::string &word, const std::string &ruby)
      {
        if (word.empty()) { return false; }
        try {
          font *f = object_cast<font *>(font_obj);
          color *c = object_cast<color *>(color_obj);
          boost::shared_ptr<image> img;
          if (ruby.empty()) {
            img.reset(image::string(word, f, c));
            return ReserveImage(word, img);
          }
          else
          {
            boost::shared_ptr<font> f_ruby(f->clone());
            f_ruby->set_point_size(f->get_point_size() / 2);
            boost::shared_ptr<image> img_ruby(image::string(ruby, f_ruby.get(), c));
            boost::shared_ptr<image> img_word(image::string(word, f, c));
            if (!img_ruby || !img_word) { throw -1; }
            int h = img_ruby->get_h() + img_word->get_h();
            int w = img_ruby->get_w();
            if (img_word->get_w() > w) { w = img_word->get_w(); }

            img.reset(image::create(w, h));
            img->blit(img_ruby.get(), (w - img_ruby->get_w()) / 2, 0);
            img->blit(img_word.get(), (w - img_word->get_w()) / 2, img_ruby->get_h());
            return ReserveImage((boost::format("{ruby,%s,%s}") % word % ruby).str(), img);
          }
        }
        catch (...) {
          return false;
        }
      }

      bool SetOnHover(const std::string &name, luabind::object hover_func)
      {
        if (name_to_index.find(name) == name_to_index.end()) { return false; }
        int i = name_to_index[name];
        hover_funcs[i] = hover_func;
        return true;
      }

      bool ShowIndex(int index)
      {
        int col_index = index_to_col[index];
        int row_index = index_to_row[index];

        int y = 0;
        for (int i = 0; i <= row_index; i++)
        {
          y += CalcRowHeight(rows[i]);
        }
        y -= rows[row_index][col_index]->get_h();

        int x = 0;
        const std::vector<boost::shared_ptr<image> > &row = rows[row_index];
        for (int i = 0; i < col_index; i++)
        {
          x += row[i]->get_w();
        }

        if (hover_imgs.find(index) != hover_imgs.end())
        {
          clickable_areas[index].assign_position_size(vector(x, y),
                                                      rows[row_index][col_index]->get_size());
        }
        if (actives.size() <= index)
        {
          actives.resize(index + 1);
          coordinates.resize(index + 1);
        }
        actives[index] = rows[row_index][col_index];
        coordinates[index] = vector(x, y);
        return true;
      }

      int h, w;
      int current_x;
      int last_index;
      luabind::object color_obj;
      luabind::object hover_bg_color_obj;
      luabind::object hover_fg_color_obj;
      luabind::object font_obj;
      std::map<int, rect> clickable_areas;
      std::map<int, luabind::object> hover_funcs;
      std::map<int, boost::shared_ptr<image> > hover_imgs;
      std::map<int, luabind::object> lclick_funcs;
      std::map<std::string, int> name_to_index;
      std::vector<boost::shared_ptr<image> > actives;
      std::vector<vector> coordinates;
      std::vector<int> index_to_row;
      std::vector<int> index_to_col;
      std::vector<std::string> log;
      std::vector<std::vector<boost::shared_ptr<image> > > rows;
  };
  static myLayout* cast_lay(void *obj) { return (myLayout *)obj; }

  layout::layout()
    : drawable(), _obj(NULL)
  {
  }

  layout::~layout()
  {
    if (_obj) { delete cast_lay(_obj); }
  }

  bool layout::clear(const color &c)
  {
    return cast_lay(_obj)->Clear();
//    return image::clear(c);
  }

  bool layout::complete()
  {
    if (is_done()) { return false; }
//    cast_status(_status)->Clear();
    return cast_lay(_obj)->Complete();
  }

  layout* layout::create(int width_stop)
  {
    layout* img = NULL;
    try {
      img = new layout;
      img->_obj = new myLayout(width_stop);
      return img;
    }
    catch (...) {
      delete img;
      return NULL;
    }
  }

  bool layout::draw_on(canvas *cv, int x, int y, unsigned char alpha)
  {
    return cast_lay(_obj)->DrawOn(cv, x, y, alpha);
  }

  luabind::object layout::get_color()
  {
    return cast_lay(_obj)->color_obj;
  }

  luabind::object layout::get_font()
  {
    return cast_lay(_obj)->font_obj;
  }

  bool layout::is_done()
  {
    myLayout *lay = cast_lay(_obj);
    return lay->last_index >= lay->log.size();
  }

  bool layout::on_hover(int x, int y)
  {
    return cast_lay(_obj)->OnHover(x, y);
  }

  bool layout::on_left_click(int x, int y)
  {
    return cast_lay(_obj)->OnLeftClick(x, y);
  }

  bool layout::reserve_clickable(const std::string &name, image *normal, image *hover,
                         luabind::object lclick_func)
  {
    return cast_lay(_obj)->ReserveClickable(name,
                                            boost::shared_ptr<image>(normal->clone()),
                                            boost::shared_ptr<image>(hover->clone()),
                                            lclick_func);
  }

  bool layout::reserve_clickable_text(const std::string &name, const std::string &text,
                                      luabind::object lclick_func)
  {
    return cast_lay(_obj)->ReserveClickableText(name, text, lclick_func);
  }

  bool layout::reserve_image(const std::string &name, image *img)
  {
    return cast_lay(_obj)->ReserveImage(name, boost::shared_ptr<image>(img->clone()));
  }

  bool layout::reserve_new_line()
  {
    return cast_lay(_obj)->ReserveNewLine();
  }

  bool layout::reserve_word(const std::string &word, const std::string &ruby)
  {
    return cast_lay(_obj)->ReserveWord(word, ruby);
  }


  bool layout::set_color(luabind::object c)
  {
    if (! base::is_type_of(c, LEV_TCOLOR)) { return false; }
    cast_lay(_obj)->color_obj = c;
    return true;
  }

  bool layout::set_font(luabind::object f)
  {
    if (! base::is_type_of(f, LEV_TFONT)) { return false; }
    cast_lay(_obj)->font_obj = f;
    return true;
  }

  bool layout::set_on_hover(const std::string &name, luabind::object hover_func)
  {
    return cast_lay(_obj)->SetOnHover(name, hover_func);
  }

  bool layout::show_next()
  {
    if (is_done()) { return false; }
    myLayout *lay = cast_lay(_obj);
    return lay->ShowIndex(lay->last_index++);
  }

  */
}

