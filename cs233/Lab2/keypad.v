module keypad(valid, number, a, b, c, d, e, f, g);
   output 	valid;
   output [3:0] number;
   input 	a, b, c, d, e, f, g;
   wire		ad, cd, be, af, cf, bd, ce, bf, ae, bg;

   and a1(ad, a, d);				// ad - 1
   and a2(cd, c, d);				// cd - 3
   and a3(be, b, e);				// be - 5
   and a4(af, a, f);				// af - 7
   and a5(cf, c, f);				// cf - 9
   and a6(bd, b, d);				// bd - 2
   and a7(ce, c, e);				// ce - 6
   and a8(bf, b, f);				// bf - 8
   and a9(ae, a, e);				// ae - 4
   and a0(bg, b, g);				// bg - 0

   or o1(number[0], ad, cd, be, af, cf);
   or o2(number[1], bd, cd, ce, af);
   or o3(number[2], ae, be, ce, af);
   or o4(number[3], bf, cf);

   or o5(valid, bg, ad, bd, cd, ae, be, ce, af, bf, cf);

endmodule // keypad
