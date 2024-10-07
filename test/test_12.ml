let () =
  Magick.magick_core_genesis ();

  let e = Magick.magick_exception_info_acquire () in
  let nf = Magick.magick_image_info_clone () in
  let d = Magick.magick_draw_info_acquire () in

  Magick.magick_image_info_set_filename nf "xc:white";
  Magick.magick_image_info_set_size nf "120x80";

  begin
    let img = Magick.magick_image_read nf e in

    let font = "/usr/share/fonts/truetype/freefont/FreeSansBold.ttf" in
    Magick.magick_draw_info_set_font d font;
    Magick.magick_draw_info_set_pointsize d 26.0;

    Magick.magick_draw_info_set_fill d (0, 0, 65535, 0);
    Magick.magick_draw_info_set_primitive d "text 20,40 'hello'";

    Magick.magick_image_draw img d;
 
    Magick.magick_image_display nf img;
    Magick.magick_image_destroy img;
  end;

  Magick.magick_exception_info_destroy e;
  Magick.magick_image_info_destroy nf;
  Magick.magick_draw_info_destroy d;

  Magick.magick_core_terminus ();
;;
