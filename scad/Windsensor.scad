$fn=100;
module cup(r=12, R=40, t=4){
    difference() {
        union() {
        sphere(r=r);
        translate([-10,0,0])
        rotate([0,0,-8])
          cube([7,R,3]);
        }
        translate([t,0,0])
    sphere(r=r);
        translate([2*r,0,0])
     cube([4*r,4*r,4*r],center=true);
    }
    
}

// full printed anemometer
module anenometer() {
difference() {
    union() {
       scale([1,1,0.5])
         sphere(r=8);
    cylinder(r=8,h=15);
    translate([0,0,-11]) {
    cylinder(r=5,h=25);
       scale([1,1,0.5])
         sphere(r=5);
    }
    translate([0,-40,-12])
      cup();
    rotate([0,0,120])
      translate([0,-40,-12])
        cup();
    rotate([0,0,-120])
    translate([0,-40,-12])
    cup();
    }
    // 12mm bearing
    translate([0,0,2])
    cylinder(r=6,h=20);
    
    // magnet holes
    translate([0,0,12]) {
    translate([0,0,0])
     rotate([90,0,0])
      cylinder(r=2,h=15, center=true);
    }
    //ring cutaway
    translate([0,0,8])
    difference() {
    cylinder(r=14,h=20);
    cylinder(r=8,h=20);
    }   
    
}
}
// cups only
module cup2(d=32, R=50, t=1.5){
    difference() {
        union() {
            sphere(d=d);
            // stub
            translate([-5,2,11])
            rotate([80,0,0]) 
             scale([1,0.7,1])
              union() {
                  
                cylinder(d=8,h=15);
               translate([0,0,15])
   
                   scale([1,1,2])
                  sphere(d=8);
   
            }
        }
        translate([t,0,0])
         sphere(d=d-t);
        translate([d,0,0])
            cube([2*d,4*d,4*d],center=true);
        // arm hole
            translate([-5,2,11])
            rotate([80,0,0]) 
             translate([0,0,4])
             scale([1,1,1])                  
                cylinder(d=4,h=20);
    };
}

module shaftarm(a=0) {
  rotate([-10,0,a])
    translate([0,0,-5])
    rotate([-90,0,0]) 
             scale([1,0.6,1])
        union() {
          translate([0,0,3])
          cylinder(d1=18,d2=10, h=12);
            translate([0,0,15])
            
              scale([1,1,1.5])
             sphere(d=11);
            }

}

// shaft only with carbon arms
module shaft() {
difference() {
    union() {
    translate([0,0,-9]) {
        cylinder(r=6,h=10);
        }
    translate([0,0,-4])
        cylinder(d2=12,d1=20,h=2);
    translate([0,0,-10])
        cylinder(d=20,h=6);
        
//       shaftarm(a=0);
//      shaftarm(a=120);
//    shaftarm(a=-120);
    }
    // 2mm pilot hole, drill out to 3mm to get center
    translate([0,0,-25])
    cylinder(d=3,h=30);
    // slots for arms made of carbon bar
    // glued into place
    translate([0,0,-5])
    rotate([-10,0,0])    
     rotate([-90,0,0])
      cylinder(d=4,h=25);
    rotate([-10,0,120])
    translate([0,0,-5])
    rotate([-90,0,0])
      cylinder(d=4,h=25);
    rotate([-10,0,-120])
    translate([0,0,-5])
    rotate([-90,0,0])
      cylinder(d=4,h=25);
    
    // 
    
}
}


module body(r=14,h=69) {
    translate([0,0,0]) {
        union() {
           difference() {
            union() {
             // body
                translate([0,0,9+7]) {
                 cylinder(d=28,h=h-7);
                 scale([1,1,0.3])
                    sphere(d=28);
                    
                }
                
                translate([0,0,0])
                 cylinder(d=18,h=25);
                
                // mount arm
                translate([8,0,55])
                 rotate([0,110,0])
                 cylinder(d=15,h=25);

             }
             // space inside, 4mm wall, 20mm
             // sensor housing
             translate([0,0,-1])
               cylinder(d=20,h=h+40);
             
             
             
             
             
             // top socket
             translate([0,0,h])
             difference() { 
                cylinder(r=r+2,h=10);
                cylinder(r=r-2,h=20);
             }
             
             // mount socket
             translate([8,0,55])
                 rotate([0,110,0])
                 cylinder(d=10,h=50);

           }
           
           translate([-5,0,56])
           difference() {
              translate([1,0,-1])
              cube([4,20,40], center=true);
              // slot for board
              cube([4,18.6,40], center=true);
              translate([0,0,-2])
              cube([7,16.5,44], center=true);
           }
          
       }
       }
    }
    
module arm(d1=25,d2=15, pad=0) {
    translate([200,0,-1000-pad])
    cylinder(d1=d1,d2=d2,h=920+2*pad);
  
translate([100,0,-85])
rotate([90,0,0])
difference() {    
rotate_extrude(convexity = 10)
translate([100, 0, 0])
 circle(d = d2);
    rotate([0,0,-20+pad])
    translate([-200,0,0])
    cube([400,400,400], center=true);
    rotate([0,0,-pad])
    translate([0,-200,0])
    cube([400,400,400], center=true);
}
    
   translate([8,0,55])
       rotate([0,110,0])
         translate([0,0,25-pad])
         cylinder(d=d2,h=110+2*pad);
    
}

module mast() {
    difference() {
    arm();
    arm(d1=12,d2=12,pad=2);
        cube([400,400,400]);
    }
}

module bottombearing() {
    translate([0,0,0])
    union() {
        difference()  {
           cylinder(d=16,h=17);
            
                     // bearing hole 10mm
                 translate([0,0,6])
                   cylinder(d=10,h=15);

                 // shaft hole 3.1
                 translate([0,0,-1])
                   cylinder(d=3.1,h=20);
                 // orings
                 //translate([0,0,4])
                //   cylinder(d=5,h=20);
                 // drip shield
                 translate([0,0,-1])
                   cylinder(d=14,h=4);
        }

           // sensor holder
        translate([0,0,13])
           difference() {
            cylinder(d=20,h=10);
            translate([0,0,-1])
              cylinder(d=14,h=12);
           
            translate([0, 7.5,8.5])
               rotate([0,0,180])
               3144sensor();
           }
       }
           
}

module 3144sensor() {
    difference() {
       cube([4.1,1.6,4], center=true);
       translate([2.05,0,0])
        rotate([0,0,45])
       translate([0,-2.5,-5])
         cube([4.1,5,10]);
       translate([-2.05,0,0])
        rotate([0,0,-45])
       translate([-4.1,-2.5,-5])
         cube([4.1,5,10]);
    }
    
}
    
module bodytop(r=14,h=11, bh=60) {
    translate([0,0,10+bh]) {
           difference() {
        union() {
           difference() {
             union() {
               cylinder(r=r,h=h);
               cylinder(d=16,h=h+22);
               translate([0,0,h])
                scale([1,1,0.3])
                  sphere(r=r);
             }
             // space inside, 2mm wall, 26mm ID
             translate([0,0,-1])
               cylinder(r=r-2,h=h-1);
           }
           
           // block for board, cut away below
           translate([0,0,7])
               cylinder(d=24,h=2);
       }
           translate([0,0,7]) {
               hull() {
                   translate([10/2,10/2,0])
                   cylinder(d=10,h=2,center=true);
                   translate([-10/2,10/2,0])
                   cylinder(d=10,h=2,center=true);
                   translate([-10/2,-10/2,0])
                   cylinder(d=10,h=2,center=true);
                   translate([10/2,-10/2,0])
                   cylinder(d=10,h=2,center=true);
               }
           }
             // 10mm bearing hole
             translate([0,0,h-10])
               cylinder(d=10,h=h+30);
             // 3.1mm shaft hole
             translate([0,0,h-10])
               cylinder(d=3.1,h=h+25);
             // oring cavity 3x1 oring, 4.9mm cavity
             // fill from base and compress with bearings
             translate([0,0,h+18])
               cylinder(d=5,h=2);
           
              // cap recess, 14mm
             translate([0,0,h+20])
           difference() {
              cylinder(d=18,h=3);
           
             translate([0,0,-1])
              cylinder(d=12,h=5);
           }
           
        }
       }
    }
    
module topseal() {
    translate([0,0,99])
    difference() {
        cylinder(d=10,h=4);
        // 3.1mm shaft hole
        translate([0,0,-1])
           cylinder(d=3.1,h=6);
        // oring cavity 3x1 oring, 4.9mm cavity
        // fill from base and compress with bearings
        translate([0,0,-1])
               cylinder(d=5,h=4); 
    }
}
    
module vane_holder() {
    translate([0,0,101.5])
    difference() {
        union() {
           
          // upper shaft
          cylinder(r=5,h=15);
          translate([0,0,15])
           scale([1,1,0.5])
             sphere(r=5);
           // cap
          translate([0,0,-15]) {
          cylinder(d=20,h=20);
          translate([0,0,20])
           scale([1,1,0.2])
             sphere(d=20);
          }
          vane_arm();
        }
        // arm hole 3mm
        translate([0,0,12])
        rotate([-90,0,0])
        cylinder(d=3,h=40);
        // recess
        translate([0,0,-16])
        cylinder(d=18,h=20);
        // 2mm shaft hole dril out to 3mm
       translate([0,0,-1])
       cylinder(d=2,h=16);


    }
    
}


module vane_arm(w=40, h=90) {
    translate([0,0,-8]) {
    difference() {
    multmatrix(m=[[1, 0, 0, 0],
                 [0,  1, -0.6, 0],
                 [0,  -0.1, 1, 0],
                 [0,  0, 0,  1]])
        union() {
            difference() {
                scale([0.1,1,1])
                cylinder(d1=w,d2=w*15/20,h=h);
                translate([-5,-50,-5])
                    cube([10,50,h+10]);
            };
            difference() {
                scale([0.1,2,1])
                cylinder(d1=w,d2=w*15/20,h=h);
                  translate([-5,0,-5])
                    cube([10,50,h+10]);
            }
        }
        translate([-5,0,-5])
          cube([10,50,25]);
             
        // top corner
        translate([0,-48,74.5])
        rotate([0,90,0])
        intersection() {
            difference() {
               cylinder(d=50,h=15, center=true);
               cylinder(d=30,h=17, center=true);
            }
           rotate([0,0,0])
           translate([-25,25,0])
           cube([50,50,30], center=true);
           rotate([0,0,29])
           translate([-25,25,0])
           cube([50,50,30], center=true);
        }
        // top back corner
        translate([0,-77.4,88.5])
        
        rotate([0,90,0])
        intersection() {
            difference() {
               cylinder(d=40,h=15, center=true);
               cylinder(d=8,h=17, center=true);
            }
            union() {
           rotate([0,0,90])
           translate([-25,25,0])
           cube([50,50,30], center=true);
           rotate([0,0,108])
           translate([-25,25,0])
           cube([50,50,30], center=true);
            }
        }
        // lower corner
        translate([0,-34,13])
        
        rotate([0,90,0])
        intersection() {
            difference() {
               cylinder(d=40,h=15, center=true);
               cylinder(d=20,h=17, center=true);
            }
           rotate([0,0,198])
             translate([-25,25,0])
               cube([50,50,30], center=true);
           rotate([0,0,180])
             translate([-25,25,0])
               cube([50,50,30], center=true);
        }

    }
    }
}

module magnet_holder() {
    translate([0,0,80.5])
    difference() {
     cylinder(d=8,h=9);
     translate([0,0,-1])
       cylinder(d=6,h=6);
     translate([0,0,-1])
       cylinder(d=3,h=10);
    }
}

// not used
module magnet_holder8() {
    translate([0,0,80.5])
    difference() {
     cylinder(d=8,h=9);
     translate([0,0,-1])
       cylinder(d=8.1,h=2);
     translate([0,0,-1])
       cylinder(d=3.1,h=10);
    }
}

module magnet_holder_ano() {
    translate([0,0,18])
    difference() {
     cylinder(d=12,h=5);
        //shaft hole
        translate([0,0,-1])
        cylinder(d=3,h=7);
        // magnet hole
        translate([0,6,2.5])
          rotate([90,0,0])
           cylinder(d=3,h=2.5);
        translate([0,-6,2.5])
        rotate([-90,0,0])
           cylinder(d=3,h=2.5);
        
    }
}


// not printed
module bearing() {
    color("red")
    difference() {
        cylinder(d=9,h=4);
        translate([0,0,-1])
        cylinder(d=3,h=6);
        
    }
}

module vaneshaft() {
    color("silver")
    cylinder(d=3,h=30);
}
module anoshaft() {
    color("silver")
    cylinder(d=3,h=30);
}
    
module magnet() {
    color("black")
    cylinder(d=6,h=4);
}

module minpro() {
    color("green")
    cube([2,18.5,34],center=true);
}

module az6500() {
    color("blue")
   hull() {
                   translate([10/2,10/2,0])
                   cylinder(d=10,h=1.5);
                   translate([-10/2,10/2,0])
                   cylinder(d=10,h=1.5);
                   translate([-10/2,-10/2,0])
                   cylinder(d=10,h=1.5);
                   translate([10/2,-10/2,0])
                   cylinder(d=10,h=1.5);
   }
   translate([0,0,3.5/2])
   cube([5,4,3.5], center=true);

}

module render() {
//mast();
translate([0,40,-24])
cup2();
rotate([0,0,120])
 translate([0,40,-24])
   cup2();
rotate([0,0,-120])
 translate([0,40,-24])
   cup2();
//anenometer();
translate([0,0,-10])
   anoshaft();
translate([0,0,6])
  bearing();
translate([0,0,13])
  bearing();
 translate([-5,0,52.5])
   minpro();
translate([0,0,76.5])
   az6500();
translate([0,0,80.5])
   magnet();
translate([0,0,85])
   vaneshaft();

translate([0,0,90])
  bearing();
translate([0,0,95])
  bearing();

difference() {
    union() {
        magnet_holder();
        magnet_holder_ano();
        bodytop();
        topseal();
        shaft();
        vane_holder();
        body();
        bottombearing();
        
    }
    translate([0,0,-50])
    cube([50,50,200]);
}
}

//3144sensor();
render();
// stl

//        bodytop();
//        bearing();
//        body();
//        topseal();
//        magnet_holder();
//        magnet_holder_ano();
//vane_holder();
//        bottombearing();

// TODO
       // shaft();
//cup2();