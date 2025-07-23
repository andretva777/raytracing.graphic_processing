//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

int main() {
    hittable_list world;

    // Chão escuro difuso
    auto ground_material = make_shared<lambertian>(color(0.05, 0.05, 0.08));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    // "Sol" - esfera grande brilhante ao fundo
    auto sun_material = make_shared<metal>(color(1.0, 0.95, 0.7), 0.0);
    world.add(make_shared<sphere>(point3(0, 10, -30), 8.0, sun_material));

    // Planetas (esferas menores, alinhadas em perspectiva)
    // Mercúrio (pequeno, metálico)
    auto mercury_material = make_shared<metal>(color(0.8, 0.8, 0.7), 0.1);
    world.add(make_shared<sphere>(point3(-3.5, 0.5, -6), 0.5, mercury_material));

    // Vênus (vidro)
    auto venus_material = make_shared<dielectric>(1.45);
    world.add(make_shared<sphere>(point3(-2.2, 0.7, -7.5), 0.7, venus_material));

    // Terra (difuso azul)
    auto earth_material = make_shared<lambertian>(color(0.2, 0.3, 0.8));
    world.add(make_shared<sphere>(point3(-0.7, 1.0, -9), 1.0, earth_material));

    // Marte (difuso avermelhado)
    auto mars_material = make_shared<lambertian>(color(0.8, 0.3, 0.2));
    world.add(make_shared<sphere>(point3(1.0, 0.8, -11), 0.8, mars_material));

    // Júpiter (grande, metálico)
    auto jupiter_material = make_shared<metal>(color(0.9, 0.8, 0.6), 0.05);
    world.add(make_shared<sphere>(point3(3.0, 1.8, -15), 1.8, jupiter_material));

    // Saturno (grande, vidro)
    auto saturn_material = make_shared<dielectric>(1.3);
    world.add(make_shared<sphere>(point3(6.0, 1.5, -19), 1.5, saturn_material));

    // Urano (azulado, metálico)
    auto uranus_material = make_shared<metal>(color(0.6, 0.8, 0.9), 0.2);
    world.add(make_shared<sphere>(point3(8.5, 1.2, -23), 1.2, uranus_material));

    // Netuno (azul escuro, difuso)
    auto neptune_material = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    world.add(make_shared<sphere>(point3(10.5, 1.1, -26), 1.1, neptune_material));

    // Plutão (pequeno, vidro)
    auto pluto_material = make_shared<dielectric>(1.6);
    world.add(make_shared<sphere>(point3(12.0, 0.4, -28), 0.4, pluto_material));

    // Câmera com profundidade de campo focando na Terra
    camera cam;
    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 1200;
    cam.samples_per_pixel = 70;
    cam.max_depth         = 25;

    cam.vfov     = 30;
    cam.lookfrom = point3(-2.0, 2.5, 2.0); // posição da câmera
    cam.lookat   = point3(-0.7, 1.0, -9.0); // foca na Terra
    cam.vup      = vec3(0, 1, 0);

    cam.defocus_angle = 0.5; // profundidade de campo
    cam.focus_dist    = (cam.lookfrom - cam.lookat).length();

    cam.render(world);
}
