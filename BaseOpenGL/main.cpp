//
//  main.cpp
//  BaseOpenGL
//  Copyright © 2018年 emery. All rights reserved.
//

#include <iostream>
#define GLM_FORCE_CTOR_INIT
/*#include "texture_source_alpha.h"
#include "gl_matrix_transform.h"
#include "gl_transform_source.h"
#include "coordinate.h"
#include "coordinate_source.h"
#include "coordinate_source_3d.h"
#include "camera_source.h"*/
//#include "camera_source_cursor.h"
//#include "gl_camera.h"
//#include "lighting_color_word_space.h"
//#include "lighting_color_view_space.h"
//#include "lighting_color_gouraud.h"
//#include "lighting_basic.h"
//#include "lighting_texture_diffuse.h"
//#include "lighting_texture_emission.h"
//#include "lighting_caster_directional.h"
//#include "lighting_caster_attenuation.h"
#include "lighting_caster_flashlight.h"
int main(int argc, const char * argv[]) {
    
   // hello_triangle_main();
    
   // shader_sample_main();

  //  texture_source_main();

   // texture_main();

   //texture_source_change_main();

  //texture_source_alpha_main();

   //maxtrix_transform_test();
  // gl_matrix_transform_main();
  // gl_trans_form_source_main();

    //coordinate_main();
    //coordinate_source_3d_main();
   // camera_source_main();
   //camera_source_cursor_main();
    //gl_camera_main();
    //lighting_color_word_space_main();
    //lighting_color_view_space_main();
    //lighting_color_gouraud_main();
    //lighting_basic_main();
    //lighting_texture_diffuse_main();
    //lighting_texture_emission_main();
    //lighting_caster_main();
    lighting_caster_flashlight_main();
    return 0;
    
}
