

in_color: f32v3 $Input(0);

out_color: f32v4 $Output(0);

out_color = f32v4.(in_color.y-in_color.z+0.25*2->f32+0.5, in_color.y, in_color.z, 1.0);

