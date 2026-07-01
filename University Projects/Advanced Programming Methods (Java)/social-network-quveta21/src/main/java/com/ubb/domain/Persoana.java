package com.ubb.domain;

public class Persoana extends User {
    private String nume;
    private String prenume;
    private String dataNasterii;
    private String ocupatie;

    public Persoana(long id, String username, String email, String password, String nume, String prenume, String dataNasterii, String ocupatie) {
        super(id, username, email, password);
        this.nume = nume;
        this.prenume = prenume;
        this.dataNasterii = dataNasterii;
        this.ocupatie = ocupatie;
    }

    public String getNume() {
        return nume;
    }

    public String getPrenume() {
        return prenume;
    }

    public String getDataNasterii() {
        return dataNasterii;
    }

    public String getOcupatie() {
        return ocupatie;
    }

    @Override
    public String toString() {
        return "Persoana{" +
                "username='" + getUsername() + '\'' +
                ", nume='" + nume + '\'' +
                ", prenume='" + prenume + '\'' +
                ", dataNasterii='" + dataNasterii + '\'' +
                ", ocupatie='" + ocupatie + '\'' +
                '}';
    }
}
