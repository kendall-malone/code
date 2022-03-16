public class Vector {

    private double x;
    private double y;

    /**
     *  @param x
     * @param y
     */
    public Vector(double x, double y){ //constructor
        this.x = x;
        this.y = y;
    }

    /**
     *
     * @param a
     * @return
     */
    public boolean equals(Object a){
        if ( a == null){
            return false;
        }
        if(this.getClass() != a.getClass()){
            return false;
        }
        Vector v = (Vector) a;
            return this.x == v.x && this.y == v.y;
    }

    /**
     *
     */
    public Vector(){
        x = 0;
        y = 0;
    }

    /**
     *
     * @return
     */
    public double getX() {
        return x;
    }

    /**
     *
     * @return
     */
    public double getY() {
        return y;
    }

    /**
     *
     * @param x
     */
    public void setX(double x) {
        this.x = x;
    }

    /**
     *
     * @param y
     */
    public void setY(double y){
        this.y = y;
    }

    /**
     *
     * @param v
     * @return
     */
    public Vector plus(Vector v){
        Vector r= new Vector();
        r.x = this.x + v.getX();
        r.y = this.y + v.getY();
        return r;
    }

    /**
     *
     * @param v
     * @return
     */
    public Vector minus(Vector v){
        Vector r= new Vector();
        r.x = this.x - v.getX();
        r.y = this.y - v.getY();
        return r;
    }

    /**
     *
     * @param d
     * @return
     */
    public double dot(Vector d){
        Vector r= new Vector();
        r.x = this.x * d.getX();
        r.y = this.y * d.getY();
        double dot;
        dot = r.x + r.y;
        return dot;
    }

    /**
     *
     * @param v
     * @return
     */
    public Vector times(double v){
        Vector r= new Vector();
        r.x = this.x * 3;
        r.y = this.y * 3;
        return r;
    }

    /**
     *
     * @param v
     * @return
     */
    public double distanceTo(Vector v){
        Vector r= new Vector();
        r.x = v.x - this.x;
        r.y = v.y - this.y;
        double distance;
        double x;
        double y;
        x = r.x * r.x;
        y = r.y * r.y;
        distance = Math.sqrt(x + y);
        return distance;
    }

    /**
     *
     * @return
     */
    public String toString(){
        String s = new String();
        s = "<" + this.x + ", " + this.y + ">";
        return s;
    }


}
