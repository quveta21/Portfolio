module com.example.lab6 {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires net.synedra.validatorfx;
    requires org.kordamp.bootstrapfx.core;
    requires java.desktop;
    requires java.sql;
    requires javafx.graphics;
    requires jbcrypt;

    opens com.ubb to javafx.fxml;
    exports com.ubb;
    exports com.ubb.application;
    opens com.ubb.application to javafx.fxml;
}