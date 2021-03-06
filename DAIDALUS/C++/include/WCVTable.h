/*
 * Copyright (c) 2012-2015 United States Government as represented by
 * the National Aeronautics and Space Administration.  No copyright
 * is claimed in the United States under Title 17, U.S.Code. All Other
 * Rights Reserved.
 */

#ifndef WCVTABLE_H_
#define WCVTABLE_H_


#include "Units.h"
#include "ParameterTable.h"
#include "ParameterData.h"
#include <string>

namespace larcfm {

class WCVTable : public ParameterTable {
public:
  double DTHR; // Distance threshold
  double ZTHR; // Vertical threshold
  double TTHR; // Time threshold
  double TCOA; // Time to co-altitude threshold

  WCVTable(double dthr, double zthr, double tthr, double tcoa);

public:
  WCVTable();

  static WCVTable NASA();
  static WCVTable MITLL();

  /** Copy constructor */
  WCVTable(const WCVTable& t);

  WCVTable copy() const;

  /** copy values from t into this object */
  void copyValues(const WCVTable& t);

  double getDTHR() const;
  double getDTHR(const std::string& u) const;

  double getZTHR() const;
  double getZTHR(const std::string& u) const;

  double getTTHR() const;
  double getTTHR(const std::string& u) const;

  double getTCOA() const;
  double getTCOA(const std::string& u) const;

  void setDTHR(double val);
  void setDTHR(double val, const std::string& u);

  void setZTHR(double val);
  void setZTHR(double val, const std::string& u);

  void setTTHR(double val);
  void setTTHR(double val, const std::string& u);

  void setTCOA(double val);
  void setTCOA(double val, const std::string& u);

  ParameterData getParameters() const;
  void updateParameterData(ParameterData& p) const;
  void setParameters(const ParameterData& p);

  bool equals(const WCVTable& t2) const;

  std::string toString() const;

  bool contains(const WCVTable& tab) const;

};

}

#endif
