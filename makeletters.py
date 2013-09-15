
from xml.etree.ElementTree import QName, ElementTree, Element, SubElement, register_namespace
from sys import stdout, stderr

letters = "HALFTENTIMEACQUARTERTOTWENTYLFIVEPASTOMAFOUREIGHTWONEGOTENINEATSIXATHREELEVENTWELVENWAKESEVENFIVEUPSLEEPOCLOCK";


class SVG(object):
    def __getattr__(self, name):
        def f(*children, **kwargs):
            qname = QName("http://www.w3.org/2000/svg", name)
            e = Element(qname, **kwargs)
            e.extend(children)
            return e
        return f

svg = SVG()


register_namespace('svg', "http://www.w3.org/2000/svg")

root = svg.svg(
    # fill
    svg.rect(x="0", y="0", width="85", height="85", fill="#000000"),
    width="8.5in",
    height="11in",
    viewBox="0 0 85 110",
    version="1.1",
);
letters_elem = svg.g()
circles_elem = svg.g()

x = 0
y = 0
for letter in letters:
    px = (x * 7.0) + 5
    py = (y * 7.8) + 5

    label = svg.text(
        x=str(px),
        y=str(py),
        fill="#ffffff",
        attrib={
            "font-family": "Transport",
            "font-size": "5",
            "text-anchor": "middle"
        }
    )
    label.text = letter

    letters_elem.append(
        label
    )

    circles_elem.append(
        svg.circle(
            cx=str(px),
            cy=str(py),
            r="2.5",
            stroke="#007f00",
            fill="#007f00",
            opacity="0.25",
            attrib={
                "stroke-width": "0",
                "stroke-opacity": "0.25"
            }
        )
    )

    x += 1
    if x > 10:
        x = 0
        y += 1

root.append(letters_elem)
root.append(circles_elem)
# flora shape
root.append(
    svg.circle(
        cx=str(50),
        cy=str(50),
        r="8.75",
        stroke="#007f00",
        fill="#007f00",
        opacity="0.25",
    )
)

tree = ElementTree(root)
tree.write(stdout)
print ""

#print d(root)
