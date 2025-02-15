

in_color: v3f32 $Input(0);

out_color: v4f32 $Output(0);

out_color = v4f32.(in_color.x, in_color.y, in_color.z, 1.0);

