/* This file is an image processing operation for GEGL
 *
 * GEGL is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * GEGL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GEGL; if not, see <https://www.gnu.org/licenses/>.
 *
 * Credit to Øyvind Kolås (pippin) for major GEGL contributions
 * 2025 Beaver Aura Distortion 
* 

id=x 
dst-over aux=[ ref=x 
id=0
 
cubism tile-size=14 seed=0
median-blur radius=19 alpha-percentile=50 abyss-policy=none
lb:distorted-aura
gaussian-blur std-dev-x=1 std-dev-y=1 abyss-policy=none clip-extent=none
color-overlay value=#ffd803
median-blur radius=0 abyss-policy=none 
id=1 gimp:layer-mode layer-mode=overlay composite-mode=auto aux=[ ref=1 noise-solid detail=1 x-size=13 y-size=13 ] 
crop aux=[ ref=x  ]
opacity value=0.5
]

 */


#include "config.h"
#include <glib/gi18n-lib.h>

#ifdef GEGL_PROPERTIES


property_boolean (isolate, _("Isolate Aura?"), FALSE)

property_boolean (noise_texture, _("Noise texture?"), TRUE)

/*
enum_start (gegl_gimplayershadow_grow_shapedistort)
  enum_value (GEGL_DROPSHADOW_GROW_SHAPE_SQUARE,  "square",  N_("Square"))
  enum_value (GEGL_DROPSHADOW_GROW_SHAPE_CIRCLE,  "circle",  N_("Circle"))
  enum_value (GEGL_DROPSHADOW_GROW_SHAPE_DIAMOND, "diamond", N_("Diamond"))
enum_end (GeglgimplayershadowGrowShapedistort)
*/
property_double (noise_scale, _("Scale of Noise"), 13.0)
  description   (_("Horizontal aura offset"))
  value_range      (1.0, 16.0)
  ui_range      (1.0, 16.0)
  ui_steps      (1, 10)
  ui_meta       ("unit", "pixel-distance")



property_double (x, _("X Horizontal Movability"), 0.0)
  description   (_("Horizontal aura offset"))
  value_range      (-5.0, 5.0)
  ui_range      (-5.0, 5.0)
  ui_steps      (1, 10)
  ui_meta       ("unit", "pixel-distance")
  ui_meta       ("axis", "x")

property_double (y, _("Y Veritical Movability"), 0.0)
  description   (_("Vertical aura offset"))
  value_range      (-5.0, 5.0)
  ui_range      (-5.0, 5.0)
  ui_steps      (1, 10)
  ui_meta       ("unit", "pixel-distance")
  ui_meta       ("axis", "y")

property_double (radius, _("Aura Blur Radius"), 1)
   description (_("Blur the aura"))
   value_range (0.0, 6.0)
   ui_range    (0.24, 6.0)
   ui_gamma    (3.0)
   ui_meta     ("unit", "pixel-distance")

/*
property_enum   (growshape, _("Grow shape"),
                 GeglgimplayershadowGrowShapedistort, gegl_gimplayershadow_grow_shapedistort,
                 GEGL_DROPSHADOW_GROW_SHAPE_DIAMOND)
  description   (_("The base shape to expand the aura in"))
*/

property_double (grow_radius, _("Aura Grow radius"), 2.0)
  value_range   (0.0, 5.0)
  ui_range      (0.0, 5.0)
/*  ui_digits     (0)
  ui_steps      (1, 5)
*/
  ui_gamma      (1.5)
  ui_meta       ("unit", "pixel-distance")
  description (_("Grow the aura"))

property_color (color, _("Color"), "#ffc112")
    description (_("The color of the aura"))


property_double (opacity, _("Aura Opacity"), 1.0)
   description (_("HyperOpacity of the aura"))
   value_range (0.0, 2.0)
   ui_range    (0.0, 2.0)
   ui_gamma    (1.0)
   ui_meta     ("unit", "pixel-distance")


property_double (tile_size, _("Aura internal tile size"), 10.0)
    description (_("Internal cubism for Aura's tile size"))
    value_range (1.0, 20.0)
    ui_meta     ("unit", "pixel-distance")


property_double (displace_amount_x, _("Displace Horizontally"), -67.0)
    description (_("Displace multiplier for X or radial direction."))
    value_range (-100.0, 100.0)
    ui_range    (-100.0, 100.0)
    ui_meta     ("unit", "pixel-distance")
    ui_meta     ("label", "[displace-mode {cartesian} : cartesian-label,"
                          " displace-mode {polar}     : polar-label]")
    ui_meta     ("cartesian-label", _("Horizontal displacement"))
    ui_meta     ("polar-label", _("Pinch"))
    ui_meta     ("description", "[displace-mode {cartesian} : cartesian-description,"
                                " displace-mode {polar}     : polar-description]")
    ui_meta     ("cartesian-description", _("Displacement multiplier for the horizontal direction"))
    ui_meta     ("polar-description", _("Displacement multiplier for the radial direction"))

property_double (displace_amount_y, _("Displace Vertically"), -84.0)
    description (_("Displace multiplier for Y or tangent (degrees) direction"))
    value_range (-100.0, 100.0)
    ui_range    (-100.0, 100.0)
    ui_meta     ("unit", "pixel-distance")
    ui_meta     ("label", "[displace-mode {cartesian} : cartesian-label,"
                          " displace-mode {polar}     : polar-label]")
    ui_meta     ("cartesian-label", _("Vertical displacement"))
    ui_meta     ("polar-label", _("Whirl"))
    ui_meta     ("description", "[displace-mode {cartesian} : cartesian-description,"
                                " displace-mode {polar}     : polar-description]")
    ui_meta     ("cartesian-description", _("Displacement multiplier for the vertical direction"))
    ui_meta     ("polar-description", _("Displacement multiplier for the angular offset"))

property_double (scale, _("Scale"), 1.9)
    description (_("Reverse scaling size of the noise"))
    value_range (0.1, 8.0)
    ui_range    (0.1, 3.0)


property_int    (x_stretch, _("Stretch X"), 370)
    description (_("Stretch the noise horizontally"))
    value_range (300, 800)
    ui_range    (300, 800)
    ui_meta     ("unit", "pixel-distance")

property_int (y_stretch, _("Stretch Y"), 426)
    description(_("Stretch the noise vertically"))
    value_range (300, 800)
    ui_range    (300, 800)
    ui_meta     ("unit", "pixel-distance")

property_int    (liquid, _("Liquid"), 3)
    description (_("Intensity of the liquid distortion on the rings"))
    ui_range    (0, 4)
    value_range (0, 4)

property_seed (seed, _("Random seed"), rand)




#else

#define GEGL_OP_META
#define GEGL_OP_NAME     greataura
#define GEGL_OP_C_SOURCE greataura.c

#include "gegl-op.h"




typedef struct
{
GeglNode *move;
GeglNode *cubism;
GeglNode *distort;
GeglNode *color;
GeglNode *blur;
GeglNode *behind;
GeglNode *opacity;
GeglNode *medianfix;
GeglNode *median;
GeglNode *crop;
GeglNode *none;
GeglNode *id;
GeglNode *noise;
GeglNode *overlay;
GeglNode *input;
GeglNode *output;
} State;



static void attach (GeglOperation *operation)
{
  GeglNode *gegl = operation->node;
  GeglProperties *o = GEGL_PROPERTIES (operation);

  State *state = o->user_data = g_malloc0 (sizeof (State));

state->input    = gegl_node_get_input_proxy (gegl, "input");
  state->output   = gegl_node_get_output_proxy (gegl, "output");


 state->move   = gegl_node_new_child (gegl,
                                  "operation", "gegl:translate",  NULL);

  state->cubism   = gegl_node_new_child (gegl,
                                  "operation", "gegl:cubism",  NULL);

  state->id   = gegl_node_new_child (gegl,
                                  "operation", "gegl:nop",  NULL);



  state->distort   = gegl_node_new_child (gegl,
                                  "operation", "lb:liquid-noise-distortion",  NULL);


  state->overlay   = gegl_node_new_child (gegl,
                                  "operation", "gimp:layer-mode", "layer-mode", 23, "composite-mode", 0,  NULL);

  state->noise   = gegl_node_new_child (gegl,
                                  "operation", "gegl:noise-solid", "detail", 2,  NULL);

  state->crop   = gegl_node_new_child (gegl,
                                  "operation", "gegl:crop",   NULL);



  state->none   = gegl_node_new_child (gegl,
                                  "operation", "gegl:dst",   NULL);



  state->opacity   = gegl_node_new_child (gegl,
                                  "operation", "gegl:opacity",  NULL);

state->behind = gegl_node_new_child (gegl, "operation", "gegl:dst-over", NULL);



  state->color   = gegl_node_new_child (gegl,
                                  "operation", "gegl:color-overlay",  NULL);

   state->blur      = gegl_node_new_child (gegl, "operation", "gegl:gaussian-blur",
                                         "clip-extent", FALSE,
                                         "abyss-policy", 0, NULL);

   state->median     = gegl_node_new_child (gegl, "operation", "gegl:median-blur",
                                         "percentile",       100.0,
                                         "alpha-percentile", 100.0,
                                         "abyss-policy",      0,
                                         "neighborhood",      2,  NULL);
     

   state->medianfix     = gegl_node_new_child (gegl, "operation", "gegl:median-blur",
                                         "radius",       0,
                                         "abyss-policy",    0,
                                         NULL);


  gegl_operation_meta_redirect (operation, "color",  state->color, "value");
  gegl_operation_meta_redirect (operation, "radius",  state->blur, "std-dev-x");
  gegl_operation_meta_redirect (operation, "radius",  state->blur, "std-dev-y");
  gegl_operation_meta_redirect (operation, "grow_radius",  state->median, "radius");
  gegl_operation_meta_redirect (operation, "x",  state->move, "x");
  gegl_operation_meta_redirect (operation, "y",  state->move, "y");
  gegl_operation_meta_redirect (operation, "tile_size",  state->cubism, "tile_size");
  gegl_operation_meta_redirect (operation, "seed",  state->cubism, "seed");

  gegl_operation_meta_redirect (operation, "seed",  state->noise, "seed");

  gegl_operation_meta_redirect (operation, "noise_scale",  state->noise, "x-size");
  gegl_operation_meta_redirect (operation, "noise_scale",  state->noise, "y-size");

  gegl_operation_meta_redirect (operation, "opacity",  state->opacity, "value");

 gegl_operation_meta_redirect (operation, "scale", state->distort,  "scale");
 gegl_operation_meta_redirect (operation, "x_stretch", state->distort,  "x_stretch");
 gegl_operation_meta_redirect (operation, "y_stretch", state->distort,  "y_stretch");
 gegl_operation_meta_redirect (operation, "liquid", state->distort,  "liquid");
 gegl_operation_meta_redirect (operation, "seed", state->distort,  "seed");



 gegl_operation_meta_redirect (operation, "displace-amount-x", state->distort,  "displace-amount-x");
 gegl_operation_meta_redirect (operation, "displace-amount-y", state->distort,  "displace-amount-y");

}

static void
update_graph (GeglOperation *operation)
{
  GeglProperties *o = GEGL_PROPERTIES (operation);
  State *state = o->user_data;
  if (!state) return;
 GeglNode* blend;


if (!o->noise_texture)  blend = state->none;
if (o->noise_texture)  blend = state->overlay;


if (!o->isolate)
 gegl_node_link_many ( state->input,   state->behind, state->output,  NULL);
  gegl_node_connect (state->behind, "aux", state->opacity, "output");
   gegl_node_link_many ( state->input,  state->cubism,  state->median,  state->distort,  state->blur,   state->move,  state->color,  state->medianfix,  blend,  state->crop,  state->opacity,   NULL);
   gegl_node_connect (state->crop, "aux", state->input, "output"); 

  gegl_node_connect (blend, "aux", state->noise, "output");

if (o->isolate)
  gegl_node_link_many ( state->input,  state->cubism,  state->median,  state->distort,  state->blur,    state->move,  state->color,  state->medianfix,  blend, state->crop,  state->opacity,  state->output, NULL);
 gegl_node_connect (state->crop, "aux", state->input, "output"); 


}




static void
gegl_op_class_init (GeglOpClass *klass)
{
  GeglOperationClass *operation_class;
GeglOperationMetaClass *operation_meta_class = GEGL_OPERATION_META_CLASS (klass);
  operation_class = GEGL_OPERATION_CLASS (klass);

  operation_class->attach = attach;
  operation_meta_class->update = update_graph;

  gegl_operation_class_set_keys (operation_class,
    "name",        "lb:distorted-aura",
    "title",       _("Distorted Aura"),
    "reference-hash", "taxidriverfuturefunk",
    "description", _("Aura with a liquid distortion attempts to create a flame in default. "
                     ""),
    "gimp:menu-path", "<Image>/Filters/Artistic",
    "gimp:menu-label", _("Distorted Aura..."),
    NULL);
}

#endif
