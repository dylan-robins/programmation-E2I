#include <stdio.h>
#include <math.h>

double calc_altitude(const double ref_pressure, double mesured_pressure);

int main() {
    double sea_pressure, mesured_pressure, altitude;
    // Read the reference air pressure
    printf("Please enter the air pressure at sea level: ");
    if (scanf("%lf", &sea_pressure) == 0) {
        fprintf(stderr, "Error, please enter a valid floating point number.");
    }
    // Read the mesured air pressure
    printf("Please enter the mesured air pressure: ");
    if (scanf("%lf", &mesured_pressure) == 0) {
        fprintf(stderr, "Error, please enter a valid floating point number.");
    }

    // calculate the altitude
    altitude = calc_altitude(sea_pressure, mesured_pressure);
    printf("The mesurement was taken at %.2f meters altitude\n", altitude);
}

double calc_altitude(const double ref_pressure, const double mesured_pressure) {
    double top = 1-pow(mesured_pressure/ref_pressure, 1/5.2563);
    return top/(22.555E-6);
}
