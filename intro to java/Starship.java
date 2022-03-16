public class Starship {

    private String name;
    private Vector position;
    private Vector velocity;

    /**
     *
     * @param name
     * @param position
     */
    public Starship(String name, Vector position){ //constructor
        this.name = name;
        this.position = position;
        this.velocity = new Vector(0.0, 0.0);
    }

    /**
     *
     * @return
     */
    public String getName(){
        return name;
    }

    /**
     *
     * @return
     */
    public Vector getPosition(){
        return position;
    }

    /**
     * returns the velocity of the starship
     * @return velocity
     */
    public Vector getVelocity(){
        return velocity;
    }

    /**
     *
     * @return
     */
    public String toString(){
        String s = name + " at " + "<" + position.getX() + ", " + position.getY() + ">" + " moving " + "<" + velocity.getX() + ", " + velocity.getY() + ">" ;
        return s;
    }

    /**
     *
     * @param velocity
     * @return
     */
    public Vector accelerate(Vector velocity){
        this.velocity.setX(this.velocity.getX()+velocity.getX());
        this.velocity.setY(this.velocity.getY()+velocity.getY());
        return velocity;
    }

    /**
     *
     */
    public void drift(){
        this.position.setX(position.getX() + velocity.getX());
        this.position.setY(position.getY() + velocity.getY());
    }

}
