$fn=50;
width = 20;
length = 16;
height = 10;
rail_hole_diameter = 6.2;
rail_hole_offset = -((16 - 10) / 2);
screw_size = 4.6;

module fillet(r) {
   offset(r = r) {
     offset(r = -r) {
       children();
     }
   }
}


module screw_hole(x, y, depth, d ) {
    translate([x, y, -0.5]){
        linear_extrude(depth) {
            circle(d=d);
        }
    }
}

module outer_shell() {
    linear_extrude(height) {
        translate([0, length/4, 0]) {
            square([width, length/2], true);
        }
        fillet(3) {
            square([width, length], center=true);
        }
    }
}


module rail_hole() {
    translate([0, rail_hole_offset, 2]) {
        linear_extrude(height) {
            circle(d=rail_hole_diameter);
        }
    }
}


union() {
    difference() {
        outer_shell();
        rail_hole();
        translate([0, length/2, 0]) {
            rotate([90, 0, 0]) {
                screw_hole(0, height/2, 7, screw_size);
            }
        }
    }
}