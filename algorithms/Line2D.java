import edu.princeton.cs.algs4.Point2D;

/** A two-dimensional line through two Point2Ds, a and b. */
public class Line2D {

    private final Point2D a;

    private final Point2D b;

    public Point2D a() {
        return a;
    }

    public Point2D b() {
        return b;
    }

    public Line2D(Point2D a, Point2D b) {
        this.a = a;
        this.b = b;
    }

    /** The line from b to a. */
    public Line2D reversed() {
        return new Line2D(b, a);
    }

    /** True if p is on the left side of this line. */
    public boolean isOnLeftSide(Point2D p) {
        if (a.x() == b.x()) { // Vertical line
            return p.x() < a.x();
        }
        double d = ((b.x() - a.x()) * (p.y() - a.y()) - (b.y() - a.y()) * (p.x() - a.x()));
        return d > 0;
    }

    /** Returns the area of the triangle abp, where p is assumed to be on the left side of this line. */
    public double triangleArea(Point2D p) {
        double d = a.x()*b.y() + p.x()*a.y() + b.x()*p.y() - p.x()*b.y() - b.x()*a.y() - a.x()*p.y();
        return d / 2;
    }

}
