#include <SFML/System.hpp>
#include <Eigen/Dense>
#include <iostream>

using Eigen::MatrixXd;

int main() {
    // test libs

    sf::Time t1 = sf::microseconds(100000);
    std::cout << t1.asSeconds() << std::endl;

    MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    std::cout << m << std::endl;

    return 0;
}
