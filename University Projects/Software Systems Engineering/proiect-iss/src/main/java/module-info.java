module proiectiss.proiectiss {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;

    opens proiectiss.proiectiss to javafx.fxml;
    exports proiectiss.proiectiss;

    exports proiectiss.proiectiss.controller;
    opens proiectiss.proiectiss.controller to javafx.fxml;

    exports proiectiss.proiectiss.domain;
    opens proiectiss.proiectiss.domain to javafx.base;
}