package lab1.models;

import java.util.Objects;

public class ComplexNumber {
    private double re;
    private double im;

    public ComplexNumber(double re, double im) {
        this.re = re;
        this.im = im;
    }

    @Override
    public boolean equals(Object object) {
        if(object == this) {
            return true;
        }
        if(!(object instanceof ComplexNumber complexNumber)) {
            return false;
        }

        return Objects.equals(this.re, complexNumber.re) && Objects.equals(this.im, complexNumber.im);
    }

    public ComplexNumber adunare(ComplexNumber complexNumber) {
        this.setRe(this.getRe() + complexNumber.getRe());
        this.setIm(this.getIm() + complexNumber.getIm());
        return this;
    }

    public ComplexNumber scadere(ComplexNumber complexNumber) {
        this.setRe(this.getRe() - complexNumber.getRe());
        this.setIm(this.getIm() - complexNumber.getIm());
        return this;
    }

    public ComplexNumber inmultire(ComplexNumber complexNumber) {
        this.setRe(this.getRe() * complexNumber.getRe() - this.getIm() * complexNumber.getIm());
        this.setIm(this.getRe() * complexNumber.getIm() + this.getIm() * complexNumber.getRe());
        return this;
    }

    public ComplexNumber impartire(ComplexNumber complexNumber) {
        this.inmultire(this.conjugatul());
        this.setRe( this.getRe() / (this.getRe() * this.getRe() + complexNumber.getRe() * complexNumber.getRe()));
        this.setIm( this.getIm() / (this.getRe() * this.getRe() + complexNumber.getRe() * complexNumber.getRe()));
        return this;
    }

    public ComplexNumber conjugatul() {
        return new ComplexNumber(this.getRe(), -this.getIm());
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
