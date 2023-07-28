
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

`0x02039800 - 0x02040000`

- Space from `0x02039800` with size `0x2000` use as generic buffer for swap
- Space from `0x0203B800` with size `0x2000` use as generic buffer for swap
- Space from `0x0203E000` with size `0x1000` holds save data from expanded units and others, DON'T touch!

These spaces is free to use but during prepscreen.
