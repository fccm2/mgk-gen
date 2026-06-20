let () =
  Magick.magick_core_genesis ();

  let e = Magick.magick_exception_info_acquire () in
  let nf = Magick.magick_image_info_clone () in
  let d = Magick.magick_draw_info_acquire () in

  Magick.magick_image_info_set_filename nf "xc:white";
  Magick.magick_image_info_set_size nf "80x80";

  begin
    let img = Magick.magick_image_read nf e in

    (* fill-rectangle *)

    Magick.magick_draw_info_set_fill d (0, 65535, 0, 65535);
    Magick.magick_draw_info_set_primitive d "rectangle 20,20 60,60";

    Magick.magick_image_draw img d e;

    (* stroke-rectangle *)

    Magick.magick_draw_info_set_stroke d (0, 0, 65535, 65535);
    Magick.magick_draw_info_set_stroke_width d 3.0;
    Magick.magick_draw_info_set_primitive d "rectangle 20,20 60,60";

    Magick.magick_image_draw img d e;

    (* stroke-circle *)

    (*
    let r = (5) in
    let cx, cy = (40, 40) in

    let prim_circle (cx, cy) (r) =
      (Printf.sprintf "circle %d,%d %d,%d" cx cy cx (cy + r))
    in
    *)

    Magick.magick_draw_info_set_stroke d (0, 0, 65535, 65535);
    Magick.magick_draw_info_set_stroke_width d 3.0;
    Magick.magick_draw_info_set_primitive d "circle 40,40 40,45";

    Magick.magick_image_draw img d e;

    (* end-of-draw *)
 
    Magick.magick_image_display nf img e;
    Magick.magick_image_destroy img;
  end;

  Magick.magick_exception_info_destroy e;
  Magick.magick_image_info_destroy nf;
  Magick.magick_draw_info_destroy d;

  Magick.magick_core_terminus ();
;;
