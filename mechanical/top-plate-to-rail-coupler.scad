$fn=50;
width = 26;
length = 30;
height = 10;
shelf_height = 2;
shelf_length = 12;
bearing_hole_diameter = 12.1;
bearing_hole_offset = -6;
screw_size = 3.3;
screw_spacing = 14;

module fillet(r) {
   offset(r = r) {
     offset(r = -r) {
       children();
     }
   }
}


module shelf_cutout() {
    translate([0, (length / 2) - (shelf_length / 2), height/2 + shelf_height/2]){
        linear_extrude(height - shelf_height + 0.5) {
            square([width + 0.5, shelf_length + 0.5], center=true);
        }
    }
}

module screw_hole(x, y, d) {
    translate([x, y, -0.5]){
        linear_extrude(height + 1) {
            circle(d=d);
        }
    }
}

module outer_shell() {
    linear_extrude(height) {
        fillet(3) {
            square([width, length], center=true);
        }
    }
}


module bearing_hole() {
    translate([0, bearing_hole_offset, -1]) {
        linear_extrude(height + 2) {
            circle(d=bearing_hole_diameter);
        }
    }
}

module bearing_stop() {
    translate([0, bearing_hole_offset, 0]) {
        linear_extrude(1.5) {
            difference() {
                circle(d=bearing_hole_diameter);
                circle(d=bearing_hole_diameter - 3);
            }
        }
    }
}


union() {
    difference() {
        outer_shell();
        bearing_hole();
        shelf_cutout();
        screw_hole(-screw_spacing/2, shelf_length - screw_size, screw_size);
        screw_hole(screw_spacing/2, shelf_length - screw_size, screw_size);
    }
    bearing_stop();
}