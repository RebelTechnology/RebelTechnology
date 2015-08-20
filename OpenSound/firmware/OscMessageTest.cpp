/*
g++ -g -I. -o OscMessageTest OscMessageTest.cpp -lboost_unit_test_framework && ./OscMessageTest
*/
#define SERIAL_DEBUG
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test
#include <boost/test/auto_unit_test.hpp>

#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif /* min */
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif /* max */
#ifndef abs
#define abs(x) ((x)>0?(x):-(x))
#endif /* abs */

#include <stdint.h>

class Print {
public:
  void write(char c);
  void write(uint8_t* str, int size);
};

//#define OPENSOUND_H
#include "OscMessage.hpp"

BOOST_AUTO_TEST_CASE(sanity){
  BOOST_CHECK(2+2 != 3);
}

BOOST_AUTO_TEST_CASE(testConstructor){
  OscMessage msg("/foo/bar");
  BOOST_CHECK_EQUAL(msg.getAddress(), "/foo/bar");
  BOOST_CHECK_EQUAL(msg.getSize(), 0);
}

BOOST_AUTO_TEST_CASE(testSetAddress){
  OscMessage msg("/foo");
  BOOST_CHECK_EQUAL(msg.getAddress(), "/foo");
  msg.setAddress("/bar");
  BOOST_CHECK_EQUAL(msg.getAddress(), "/bar");
  msg.addInt(0);
  msg.addFloat(0.0);
  BOOST_CHECK_EQUAL(msg.getSize(), 2);
  BOOST_CHECK_EQUAL(msg.getDataType(0), 'i');
  msg.setAddress("/foobar");
  BOOST_CHECK_EQUAL(msg.getAddress(), "/foobar");
  BOOST_CHECK_EQUAL(msg.getSize(), 2);
  BOOST_CHECK_EQUAL(msg.getDataType(0), 'i');
  BOOST_CHECK_EQUAL(msg.getDataType(1), 'f');
  msg.setAddress("/fo");
  BOOST_CHECK_EQUAL(msg.getAddress(), "/fo");
  BOOST_CHECK_EQUAL(msg.getSize(), 2);
  BOOST_CHECK_EQUAL(msg.getDataType(0), 'i');
  BOOST_CHECK_EQUAL(msg.getDataType(1), 'f');
}
