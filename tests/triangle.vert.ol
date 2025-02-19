
vertex_index: u32 $VertexIndex;

colors: [3]f32v3 = f32v3.[
    f32v3.(1.0, 0.0, 0.0),
    f32v3.(0.0, 1.0, 0.0),
    f32v3.(0.0, 0.0, 1.0)
];

color_int: u32v3 = colors[vertex_index] -> u32v3;

positions: [3]f32v2 = f32v2.[
	f32v2.( 0.0, -0.5),
	f32v2.( 0.5,  0.5),
	f32v2.(-0.5,  0.5)
];

out_position: f32v4 $VertexPosition;
out_color: f32v3 $Output(0); 

//err_me: f32v4 = out_color.xyzw;

//ok: f32v3 = out_position.zxy;

bonkers: f32v2 = out_position.xyz.yzz.zzx.yz.xy.yx.xx;


pos3: f32v3 = f32v3.(positions[vertex_index].x, positions[vertex_index].y, 0.0);

pos2: f32v2 = pos3.xy;



out_position = f32v4.(pos2.x, pos2.y, 0.0, 1.0);
out_color = colors[vertex_index];


