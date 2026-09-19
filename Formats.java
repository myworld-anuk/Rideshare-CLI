
import java.math.BigDecimal;
import java.math.RoundingMode;

/** Number-formatting helpers that reproduce the C++ program's output format. */
final class Formats {

    private Formats() {
    }

    /**
     * Fixed 4 decimal places with trailing zeros (and a dangling '.') removed,
     * e.g. 40.4269 -> "40.4269", 40.5 -> "40.5", 40.0 -> "40".
     */
    static String coordinate(double value) {
        String s = new BigDecimal(value).setScale(4, RoundingMode.HALF_EVEN).toPlainString();
        int end = s.length();
        while (end > 0 && s.charAt(end - 1) == '0') {
            end--;
        }
        if (end > 0 && s.charAt(end - 1) == '.') {
            end--;
        }
        return s.substring(0, end);
    }

    /** Shortest plain representation of a double, without a trailing ".0" (5.0 -> "5", 12.3 -> "12.3"). */
    static String miles(double value) {
        return BigDecimal.valueOf(value).stripTrailingZeros().toPlainString();
    }
}
