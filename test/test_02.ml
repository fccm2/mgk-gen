let () =
  Magick.magick_core_genesis ();

  let e = Magick.magick_exception_info_acquire () in
  let nf = Magick.magick_image_info_clone () in

  Magick.magick_image_info_set_filename nf "rose.png";

  begin
    let img = Magick.magick_image_read nf e in
 
    Magick.magick_image_set_filename img "rose2.png";
    Magick.magick_image_write nf img;
    Magick.magick_image_destroy img;
  end;

  Magick.magick_exception_info_destroy e;
  Magick.magick_image_info_destroy nf;

  Magick.magick_core_terminus ();
;;
