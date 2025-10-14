double knots_to_miles_per_minute(int knot) {
    const double nautical_mile_to_feet = 6076.0;
    const double mile_to_feet = 5280.0;
    const double minutes_in_hour = 60.0;

    double miles_per_minute = (knot * nautical_mile_to_feet / mile_to_feet) / minutes_in_hour;
    return miles_per_minute;
}