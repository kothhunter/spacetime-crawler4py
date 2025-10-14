double knots_to_miles_per_minute(int knot) {
    const double nautical_mile_to_statute_mile = 6076.0 / 5280.0;
    const double minutes_per_hour = 60.0;

    double miles_per_minute = knot * nautical_mile_to_statute_mile / minutes_per_hour;
    return miles_per_minute;
}