/*
 * Position.h
 *
 * Contact: Jeff Maddalon (j.m.maddalon@nasa.gov)
 * NASA LaRC
 * 
 * Copyright (c) 2011-2015 United States Government as represented by
 * the National Aeronautics and Space Administration.  No copyright
 * is claimed in the United States under Title 17, U.S.Code. All Other
 * Rights Reserved.
 */

#ifndef POSITION_H_
#define POSITION_H_

#include "Vect3.h"
#include "Velocity.h"
#include "LatLonAlt.h"
#include "Point.h"
#include <string>

namespace larcfm {

/**
 * This class captures a single position represented in either
 * Euclidean or Lat/Lon coordinates.  This class is immutable.<p>
 * 
 * This class is designed to be resilient, The methods do not
 * return errors when a position in the "wrong" geometry is provided.  So 
 * the method x() will return a value even when the original
 * position was provided in LatLonAlt.  The correspondence is as follows:
 * <ul>
 * <li> latitude <-> Y
 * <li> longitude <-> X
 * <li> altitude <-> alt
 * </ul>
 *  
 */
  class Position {
  private:
    LatLonAlt ll;
    Point s3;
    bool latlon;

    Position(const double x, const double y, const double z);

  public:
    /** Create an empty Position object */
    Position();

    /** Construct a new Position object from a LatLonAlt object. The position will be a Lat/Lon position. */
    Position(const LatLonAlt& lla);
    /** Construct a new Position object from a Vect3 object.  The position will be a Euclidean position. */
    Position(const Vect3& v);

    Position(const Position& p);

	/**
	 * Creates a new lat/lon position with coordinates (<code>lat</code>,<code>lon</code>,<code>alt</code>).
	 *
	 * @param lat latitude [deg north latitude]
	 * @param lon longitude [deg east longitude]
	 * @param alt altitude [ft]
	 */
	static Position makeLatLonAlt(double lat, double lon, double alt);

	/**
	 * Creates a new lat/lon position with coordinates (<code>lat</code>,<code>lon</code>,<code>alt</code>).
	 *
	 * @param lat latitude [lat_unit north latitude]
	 * @param lat_unit units of latitude
	 * @param lon longitude [lon_unit east longitude]
	 * @param lon_unit units of latitude
	 * @param alt altitude [alt_unit]
	 * @param alt_unit units of altitude
	 */
	static Position makeLatLonAlt(double lat, std::string lat_unit, double lon, std::string lon_unit, double alt, std::string alt_unit);


	/**
	 * Creates a new lat/lon position with coordinates (<code>lat</code>,<code>lon</code>,<code>alt</code>).
	 *
	 * @param lat latitude [radians]
	 * @param lon longitude [radians]
	 * @param alt altitude [m]
	 */
	static Position mkLatLonAlt(double lat, double lon, double alt);

	/**
	 * Creates a new Euclidean position with coordinates (<code>x</code>,<code>y</code>,<code>z</code>).
	 *
	 * @param x coordinate [nmi]
	 * @param y coordinate [nmi]
	 * @param z altitude [ft]
	 */
	static Position makeXYZ(double x, double y, double z);


	/**
	 * Creates a new Euclidean position with coordinates (<code>x</code>,<code>y</code>,<code>z</code>).
	 *
	 * @param x coordinate [m]
	 * @param y coordinate [m]
	 * @param z altitude [m]
	 */
	static Position mkXYZ(double x, double y, double z);


	/**
	 * Creates a new Euclidean position with coordinates (<code>x</code>,<code>y</code>,<code>z</code>).
	 *
	 * @param x coordinate [x_unit]
	 * @param x_unit units of x coordinate
	 * @param y coordinate [y_unit]
	 * @param y_unit units of y coordinate
	 * @param z altitude [z_unit]
	 * @param z_unit units of z coordinate
	 */
	static Position makeXYZ(double x, std::string x_unit, double y, std::string y_unit, double z, std::string z_unit);


//  private:
//    static Position& makeZeroLL();
//    static Position& makeZeroXYZ();
//    static Position& makeInvalid();
  public:


    /** Zero latitude, longitude and altitude */
    static const Position& ZERO_LL();
    /** Zero x, y, and z */
    static const Position& ZERO_XYZ();

    static const Position& INVALID();

    /**
     * Checks if two Positions are almost the same.
     * 
     * @param v Position for comparison
     * 
     * @return <code>true</code>, if <code>this</code> Position is almost equal 
     * to <code>v</code>.
     */
    bool almostEquals(const Position& v) const;

    /**
     * Checks if two Positions are almost the same.
     * 
     * @param pp Position for comparison
     * @param epsilon_horiz allowable horizontal deviation [m] 
     * @param epsilon_vert allowable vertical deviation [m] 
     * 
     * @return <code>true</code>, if <code>this</code> Position is almost equal 
     * to <code>v</code>.
     */
    bool almostEquals(const Position& pp, double epsilon_horiz, double epsilon_vert) const;

    /** Are these two positions equal? */
    bool operator == (const Position& v) const;
    /** Are these two positions unequal? */
    bool operator != (const Position& v) const;

	/** Return the horizontal position as a standard vect2().  This returns either (x,y), or, equivalently, (lon, lat). */
    Vect2  vect2() const;
    /** Return the three dimensional position vector */
    const Point&  point() const;
    /** Return the associated LatLonAlt object */
    const LatLonAlt& lla() const;

    /** Returns true if this Position is invalid */
    bool isInvalid() const;

    /** Return the x coordinate */
    double x() const;
    /** Return the y coordinate */
    double y() const;
    /** Return the z coordinate */
    double z() const;
    /** Return the latitude */
    double lat() const;
    /** Return the longitude */
    double lon() const;
	/** Return the altitude (internal units) */
    double alt() const;

    /** Return the latitude in degrees north */
    double latitude() const;
    /** Return the longitude in degrees east */
    double longitude() const;
    /** Return the altitude in feet */
    double altitude() const;
    /** Return the x coordinate in [nmi] */ 
    double xCoordinate() const;
    /** Return the y coordinate in [nmi] */
    double yCoordinate() const;
    /** Return the z coordinate in [ft] */
    double zCoordinate() const;

    /** Return if this Position is a latitude or longitude */
    bool isLatLon() const;

    /** Make a new Position from the current one with the X coordinate changed */
    const Position mkX(const double xx) const;  
    /** Make a new Position from the current one with the longitude changed */
    const Position mkLon(const double lon) const; 
    /** Make a new Position from the current one with the Y coordinate changed */ 
    const Position mkY(const double yy) const;  
    /** Make a new Position from the current one with the latitude changed */
    const Position mkLat(const double lat) const;
    /** Make a new Position from the current one with the Z coordinate changed */
    const Position mkZ(const double zz) const;  
	/** Make a new Position from the current one with the altitude changed (internal units) */
    const Position mkAlt(const double alt) const;

    const Position zeroAlt() const;

    /** Return the horizontal distance between the current Position and the given Position */
    double distanceH(const Position& p) const;

	/** Return the vertical distance between the current Position and the given Position.*/
    double distanceV(const Position& p) const;

	/** Return the vertical distance between the current Position and the given Position. Positive values mean 
	 * the current Position is above the given Position */
    double signedDistanceV(const Position& p) const;

    /** 
     * Perform a linear projection of the current Position with given velocity and time.  
     * If isLatLon() is true, then a great circle route is followed and the velocity 
     * represents the initial velocity along the great circle.
     * 
     * Reminder: If this is used in a stepwise fashion over lat/lon, be careful when passing 
     * over or near the poles and keep the velocity track in mind.
     * 
     *  @param v the velocity
     *  @param time the time from the current point
     *  Note: using a negative time value is the same a velocity moving in the opposite direction (along the great circle, if appropriate)
	 * @return linear projection of the position
     */
    const Position linear(const Velocity& v, double time) const;

	/**
	 * Perform a estimation of a linear projection of the current Position with the
	 * given velocity and time.
	 * @param dn  offset in north direction (m)
	 * @param de  offset in east direction  (m)
	 * @return linear projection of the position
	 */
	const Position linearEst(double dn, double de) const;


	/**
	 * Perform a estimation of a linear projection of the current Position with the 
	 * given velocity and time.
	 * @param vo the velocity
	 * @param time the time from the current point
	 * @return linear projection of the position
	 */
    const Position linearEst(const Velocity& vo, double time) const;

	/**
	 * Return the mid point between the current position and the given position
	 * @param p2 the other position
	 * @return the midpoint
	 */
    const Position midPoint(const Position& p2) const;

//	/** Return a new Position, relative to a given position (which becomes the new origin).
//	 * This is equivalent to so.Sub(si), or the GreatCircle projection.
//	 * Altitude will not be preserved.
//	 */
//    const Position relativeProjection(const Position& si) const;

	/** Return the track angle of the vector from the current Position to the given Position, based on initial course */
    double track(const Position& p) const;

    Velocity initialVelocity(const Position& p2, double time) const;

    /** return the velocity going from this to p over dt seconds.
     * Returns a ZERO velocity if dt <= 0 */
    Velocity finalVelocity(const Position& p2, double time) const;


	/** Return the track angle of the vector from the current Position to the given Position, based on representative course */
    double representativeTrack(const Position& p) const;


	// returns intersection point and time of intersection relative to position so
	// a negative time indicates that the intersection occurred in the past (relative to directions of travel of so1)
  static std::pair<Position,double> intersection(const Position& so, const Velocity& vo, const Position& si, const Velocity& vi);


	/** Returns intersection point and time of intersection relative to the time of position so
	 *  for time return value, it assumes that an aircraft travels from so1 to so2 in dto seconds and the other aircraft from si to si2
	 *  a negative time indicates that the intersection occurred in the past (relative to directions of travel of so1)
	 */
  static std::pair<Position,double> intersection(const Position& so, const Position& so2, double dto, const Position& si, const Position& si2);

	/** Determine if a loss of separation has occured (using either geodesic or Euclidean calculations)
	 *
	 * @param p2 the position of the other aircraft
	 * @param D horizontal distance to specify loss of separation
	 * @param H vertical distance to specify loss of separation
	 * @return true if there is a loss of separation
	 */
	bool LoS(const Position& p2, double D, double H);

	bool collinear(Position p1, Position p2) const;

//	/** Return the average velocity between the current position and the given position, with the given speed [internal units]. */
//    Velocity averageVelocity(const Position& p2, double speed);

    /** Return a string representation */
    std::string toString() const;

    /** Return a string representation */
    std::string toString(int prec) const;

	/**
	 * Return a string representation using the given unit conversions (latitude and longitude, if appropriate, are always in degrees, so only the z unit is used in that case)
	 */
    std::string toStringUnits() const;

	/**
	 * Return a string representation using the given unit conversions (latitude and longitude, if appropriate, are always in degrees, so only the z unit is used in that case)
	 */
    std::string toStringUnits(const std::string& xunit, const std::string& yunit, const std::string& zunit) const;

    std::vector<std::string> toStringList() const;

    std::vector<std::string> toStringList(int) const;

	/** Return a string representation with a default precision but without parentheses. */
    std::string toStringNP() const;

	/** Return a string representation, with a user-specified digits of precision (0-15) without parentheses. */
    std::string toStringNP(int precision) const;

	/** This interprets a string as a LatLonAlt position with units in deg/deg/ft or the specified units (inverse of toString()) */
	static const Position parseLL(const std::string& s);

	/** This interprets a string as a XYZ position with units in nmi/nmi/ft or the specified units (inverse of toString()) */
	static const Position parseXYZ(const std::string& s);

	/**
	 * This interprets a string into a LatLonAlt or XYZ position, if appropriate units are given.
	 * If no units are present, it returns an invalid Position.
	 */
	static const Position parse(const std::string& s);

  };

}

#endif /* POSITION_H_ */
