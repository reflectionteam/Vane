#include "ui/widgets/button/button.h"
#include <string.h>

static bool ui_button_internal(Clay_ElementId id, const char *label, bool is_active,
                               bool grow_width, const ButtonStyle *style) {
  if (!style) {
    style = &button_monochrome;
  }

  Clay_PointerData pointer = Clay_GetPointerState();
  bool hovered = Clay_PointerOver(id);
  bool pressed = hovered && (pointer.state == CLAY_POINTER_DATA_PRESSED ||
                             pointer.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME);
  bool clicked = hovered && (pointer.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME);

  Clay_Color bg;
  Clay_Color text_color;
  Clay_Color border_color;

  if (is_active) {
    if (hovered) {
      bg = style->bg_active_hover;
      text_color = style->text_active_hover;
      border_color = style->border_active_hover;
    } else {
      bg = style->bg_active;
      text_color = style->text_active;
      border_color = style->border_active;
    }
  } else {
    if (pressed) {
      bg = style->bg_active;
      text_color = style->text_active;
      border_color = style->border_active;
    } else if (hovered) {
      bg = style->bg_hover;
      text_color = style->text_hover;
      border_color = style->border_hover;
    } else {
      bg = style->bg_normal;
      text_color = style->text_normal;
      border_color = style->border_normal;
    }
  }

  Clay_String text_str = (Clay_String){
      .chars = label ? label : "",
      .length = (int32_t)(label ? strlen(label) : 0),
      .isStaticallyAllocated = false,
  };

  Clay_SizingAxis width_sizing = grow_width ? CLAY_SIZING_GROW(0) : CLAY_SIZING_FIT(0);

  CLAY(id, {.layout = {.sizing =
                           {
                               .width = width_sizing,
                           },
                       .padding = style->padding,
                       .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER}},
            .border = {.color = border_color,
                       .width = {.left = style->border_width,
                                 .right = style->border_width,
                                 .top = style->border_width,
                                 .bottom = style->border_width,
                                 .betweenChildren = 0}},
            .cornerRadius = CLAY_CORNER_RADIUS(style->border_radius),
            .backgroundColor = bg}) {
    CLAY_TEXT(text_str, CLAY_TEXT_CONFIG({.textColor = text_color, .fontSize = style->font_size}));
  }

  return clicked;
}

bool ui_button(Clay_ElementId id, const char *label, const ButtonStyle *style) {
  return ui_button_internal(id, label, false, false, style);
}

bool ui_tab_button(Clay_ElementId id, const char *label, bool is_active, const ButtonStyle *style) {
  return ui_button_internal(id, label, is_active, true, style);
}
