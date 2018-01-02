module blackbox(a, l, u, m);
    output a;
    input  l, u, m;
    wire   w02, w14, w21, w26, w27, w42, w51, w53, w60, w68, w69, w85, w88, w92, w95;

    or  o74(a, w69, w14);
    and a94(w69, w92, w27);
    or  o82(w27, w26, w51);
    not n65(w26, w51);
    and a56(w14, w60, w95);
    not n66(w95, w60);
    or  o54(w60, l, w42, w02);
    not n35(w42, u);
    not n19(w02, m);
    or  o47(w51, w85, l, w68);
    not n72(w85, u);
    not n58(w68, m);
    or  o52(w92, w88, w21);
    and a3(w88, l, u);
    and a25(w21, m, u, w53);
    not n91(w53, l);

endmodule // blackbox
