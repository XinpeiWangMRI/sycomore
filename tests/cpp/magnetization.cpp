#define BOOST_TEST_MODULE magnetization
#include <boost/test/unit_test.hpp>

#include "sycomore/magnetization.h"

BOOST_AUTO_TEST_CASE(ComplexMagnetizationFromMagnetization, *boost::unit_test::tolerance(1e-9))
{
    sycomore::Magnetization const m_r{1,2,3};
    auto && m_c = sycomore::as_complex_magnetization(m_r);

    BOOST_TEST(m_c.plus.real() == std::sqrt(2.)/2.);
    BOOST_TEST(m_c.plus.imag() == std::sqrt(2.));

    BOOST_TEST(m_c.zero == 3);

    BOOST_TEST(m_c.minus.real() == std::sqrt(2.)/2.);
    BOOST_TEST(m_c.minus.imag() == -std::sqrt(2.));
}

BOOST_AUTO_TEST_CASE(ComplexMagnetizationToMagnetization, *boost::unit_test::tolerance(1e-9))
{
    sycomore::ComplexMagnetization const m_c{
        {std::sqrt(2.)/2., std::sqrt(2.)},
        3,
        {std::sqrt(2.)/2., -std::sqrt(2.)}};

    auto && m_r = sycomore::as_real_magnetization(m_c);

    BOOST_TEST(m_r.x == 1);
    BOOST_TEST(m_r.y == 2);
    BOOST_TEST(m_r.z == 3);
}