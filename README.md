# Chicken Brooder Lamp

This arduino project connects a relay switch and an NTC thermistor to a standard 250W brooder lamp. It is powered by a 9v battery, but any method that will supply 5v will do.

## How to use

Change the `#define` values according to your setup. Also make sure your relay is connected in the NC position, so that the brooder lamp is on in case your 9v battery runs out. The last thing you want is for your chicks to be too cold!

Every week, reduce the values of MAX_TEMPERATURE and MIN_TEMPERATURE about 2.5 degrees C until they reach room temperature - around week 6.

## License

This project is licensed under the Apache v2 license. See [LICENSE](LICENSE) for more details.
