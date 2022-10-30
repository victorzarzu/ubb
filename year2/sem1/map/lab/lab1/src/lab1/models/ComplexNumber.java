package lab1.models;

import java.util.Objects;

public class NumarComplex {
    private double re;
    private double im;

    public NumarComplex(double re, double im) {
        this.re = re;
        this.im = im;
    }

    @Override
    public boolean equals(Object object) {
        if(object == this) {
            return true;
        }
        if(!(object instanceof NumarComplex)) {
            return false;
        }
        NumarComplex numarComplex = (NumarComplex)object;

        return Objects.equals(this.re, numarComplex.re) && Objects.equals(this.im, numarComplex.im);
    }

    public NumarComplex adunare(NumarComplex numarComplex) {
        this.setRe(this.getRe() + numarComplex.getRe());
        this.setIm(this.getIm() + numarComplex.getIm());
        return this;
    }

    public NumarComplex scadere(NumarComplex numarComplex) {
        this.setRe(this.getRe() - numarComplex.getRe());
        this.setIm(this.getIm() - numarComplex.getIm());
        return this;
    }

    public NumarComplex inmultire(NumarComplex numarComplex) {
        this.setRe(this.getRe() * numarComplex.getRe() - this.getIm() * numarComplex.getIm());
        this.setIm(this.getRe() * numarComplex.getIm() + this.getIm() * numarComplex.getRe());
        return this;
    }

    public NumarComplex impartire(NumarComplex numarComplex) {
        this.inmultire(this.conjugatul());
        this.setRe( this.getRe() / (this.getRe() * this.getRe() + numarComplex.getRe() * numarComplex.getRe()));
        this.setIm( this.getIm() / (this.getRe() * this.getRe() + numarComplex.getRe() * numarComplex.getRe()));
        return this;
    }

    public NumarComplex conjugatul() {
        return new NumarComplex(this.getRe(), -this.getIm());
    }

    public double getRe() {
        return re;
    }

    public void setRe(double re) {
        this.re = re;
    }

    public double getIm() {
        return im;
    }

    public void setIm(double im) {
        this.im = im;
    }
}
