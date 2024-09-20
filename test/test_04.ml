let () =
  Magick.magick_core_genesis ();

  let e = Magick.magick_exception_info_acquire () in
  let nf = Magick.magick_image_info_clone () in

  Magick.magick_image_info_set_filename nf "rose:";

  begin
    let img = Magick.magick_image_read nf e in

    let img1 = Magick.magick_image_spread img ~radius:5.2 e in
    let img2 = Magick.magick_image_sharpen img ~radius:4.1 ~sigma:3.2 e in
    let img3 = Magick.magick_image_shade img ~gray:true ~azimuth:3.0 ~elevation:2.8 e in
 
    Magick.magick_image_display nf img1;
    Magick.magick_image_display nf img2;
    Magick.magick_image_display nf img3;

    Magick.magick_image_destroy img3;
    Magick.magick_image_destroy img2;
    Magick.magick_image_destroy img1;

    Magick.magick_image_destroy img;
  end;

  Magick.magick_exception_info_destroy e;
  Magick.magick_image_info_destroy nf;

  Magick.magick_core_terminus ();
;;
