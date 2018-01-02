// Widgets Incorporated has hired you to build a widget sorter for its
// production line.  The widgets they produce are either red or blue,
// large or small, cube or spherical, and steel or plastic.

// Your widget sorter has 4 sensors:
// A scale that weighs the widget (L = 1, when the widget is large; otherwise L = 0)
// A camera that measures the color (R = 1, when the widget is red; otherwise R = 0) and
//   shape (C = 1, when the widget is cube-shaped; otherwise C = 0)
// A magnet that senses metallic objects (S = 1, when the widget is steel; otherwise S = 0)

// You need to sort the widgets into 4 bins based on their characteristics:
// Small blue spherical and blue spherical steel widgets should go in bin 2.
// Blue cube-shaped steel and red spherical steel widgets should go in bin 1.
// Large blue plastic and small red plastic widgets should go in bin 0.
// All other widgets should go in bin 3.

module widget(bin, L, R, C, S);
   output [1:0] bin;
   input  	L, R, C, S;
   wire		not_large, not_red, not_cube, not_steel, first_w, second_w, third_w, fourth_w, fifth_w, sixth_w;

   not n1(not_large, L);
   not n2(not_red, R);
   not n3(not_cube, C);
   not n4(not_steel, S);

   and a1(first_w, L, not_red, not_steel);
   and a2(second_w, not_large, R, not_steel);
   and a3(third_w, not_red, C, S);
   and a4(fourth_w, R, not_cube, S);
   and a5(fifth_w, not_large, not_red, not_steel);
   and a5(sixth_w, not_red, not_cube, S);

   or  o1(bin[0], first_w, second_w, third_w, fourth_w, fifth_w, sixth_w);
   not n5(bin[1], bin[0]);
endmodule // widget

