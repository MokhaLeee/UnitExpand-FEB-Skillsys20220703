
# UnitExpand-FEB-Skillsys20220703

Expand save unit amount to 91

----

1. `bmsave` hack
    - a.) Remove link arena.
    - b.) Remove link arena sram memory.
    - c.) Move bmsave unk-struct 1 & 2 & 3 to the tail of sram.
    - c.) Remove xmap entry.

2. `ExpandedModularSave` hack
    - a.) Refrain sram layout.
    - b.) Rewrite save-unit routine.

3. BWL memory rework
    - b.) Remove vanilla BWL table entries.
    - c.) Move unit support data to BWL table (BWL support)
    - a.) Move unit BWL skill list to unit support.

## Free RAM space consumption

`0x0203B780 - 0x0203FF80`
