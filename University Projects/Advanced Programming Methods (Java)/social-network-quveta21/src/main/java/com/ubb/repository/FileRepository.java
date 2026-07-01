//package com.ubb.repository;
//
//import com.ubb.domain.*;
//import com.ubb.exceptions.FileException;
//
//import java.io.BufferedReader;
//import java.io.FileNotFoundException;
//import java.io.FileReader;
//import java.io.IOException;
//import java.util.ArrayList;
//import java.util.Arrays;
//import java.util.List;
//
//public abstract class FileRepository<E> implements Repository<E> {
//    private final List<E> entities;
//    private final String fileName;
//
//    public FileRepository(String fileName) {
//        this.fileName = fileName;
//        this.entities = new ArrayList<>();
//        loadFromFile();
//    }
//
//    private void loadFromFile() {
//        try{
//            BufferedReader reader = new BufferedReader(new FileReader(fileName));
//            String newLine;
//            while((newLine = reader.readLine()) != null){
//                System.out.println(newLine);
//                List<String> data = Arrays.asList(newLine.split(","));
//                E entity = extractEntity(data);
//                add(entity);
//            }
//        } catch (FileNotFoundException e) {
//            throw new FileException("Eroare la deschiderea fisierului: " + fileName);
//        } catch (IOException e) {
//            throw new FileException("Eroare la citirea din fisier: " + fileName);
//        }
//
//    }
//
//    private E extractEntity(List<String> data) {
//        if (data.isEmpty()){
//            return null;
//        }
//        String username = data.get(1);
//        String password = data.get(2);
//        String  email = data.get(3);
//        switch (data.get(0)){
//            case "Persoana":
//                String nume = data.get(4);
//                String prenume = data.get(5);
//                String dataNasterii = data.get(6);
//                String ocupatie = data.get(7);
//                Persoana p = new Persoana((long) (Math.random() * 1000), username, password, email,
//                nume, prenume, dataNasterii, ocupatie);
//                break;
//            case "Duck":
//                TipRata tipRata = TipRata.valueOf(data.get(4).toUpperCase());
//                double viteza = Double.parseDouble(data.get(5));
//                double rezistenta = Double.parseDouble(data.get(6));
//                Duck d;
//                switch(tipRata) {
//                    case FLYING:
//                        d = new FlyingDuck((long) (Math.random() * 1000), username, email, password,
//                                tipRata, viteza, rezistenta);
//                        break;
//                    case SWIMMING:
//                        d = new SwimmingDuck((long) (Math.random() * 1000), username, email, password,
//                                tipRata, viteza, rezistenta);
//                        break;
//                        case FLYING_AND_SWIMMING:
//                            d = new FlyingSwimmingDuck((long) (Math.random() * 1000), username, email, password,
//                                    tipRata, viteza, rezistenta);
//                            break;
//                    default:
//                        break;
//                }
//                break;
//            default:
//                break;
//        }
//    }
//
//    @Override
//    public List<E> getAll() {
//        return entities;
//    }
//
//    @Override
//    public void add(E e) {
//        entities.add(e);
//    }
//
//    @Override
//    public void remove(E e) {
//        entities.remove(e);
//    }
//}
