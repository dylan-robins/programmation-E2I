class Point {
public:
    Point();
    Point(const double x, const double y);
    Point(const Point &a_copier);

    double abscisse();
    double ordonnee();
    double rho();
    double teta();  // teta en radians

    void translate(const double x_off, const double y_off);
    void rotation(const double angle);  // angle en radians

    void set_deg();
    void set_rad();

private:
    double _x;
    double _y;
    enum mode_t { rad,
                  deg };
    mode_t _mode;
};