#include <iostream>

struct params {
    int lang;
    int resolution_x;
    int resolution_y;
    int button_jump;
};

void init_params_copie(struct params p) {
    p.resolution_x = 1920;
    p.resolution_y = 1080;
}

void init_params_ref(struct params &p) {
    p.resolution_x = 1920;
    p.resolution_y = 1080;
}

main() {
    struct params mes_params;
    mes_params.resolution_x = 720;
    mes_params.resolution_y = 560;

    std::cout << mes_params.resolution_x << std::endl;
    std::cout << mes_params.resolution_y << std::endl;

    init_params_copie(mes_params); // ne modifie pas mes_params

    std::cout << mes_params.resolution_x << std::endl;
    std::cout << mes_params.resolution_y << std::endl;

    init_params_ref(mes_params); // modifie mes_params!

    std::cout << mes_params.resolution_x << std::endl;
    std::cout << mes_params.resolution_y << std::endl;

    return 0;
}
