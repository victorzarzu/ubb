package config;

import java.util.Properties;

public class ApplicationContext {
    private static final Properties PROPERTIES = config.Config.getProperties();

    public static Properties getPROPERTIES() {
        return PROPERTIES;
    }
}
