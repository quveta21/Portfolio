# Design System Strategy: The Curated Workspace

## 1. Overview & Creative North Star: "The Digital Atheneum"
This design system moves away from the "utilitarian tool" feel of traditional task managers and toward the concept of a **Digital Atheneum**. It is an editorial-inspired environment designed for focus, clarity, and cognitive ease. 

While inspired by the simplicity of Google Keep, we are elevating the experience through **Soft Minimalism**. We break the "template" look by utilizing intentional white space, exaggerated typographic scales, and a layout that feels "assembled" rather than "gridded." The core philosophy is **presence over pressure**: the UI should recede, leaving only the user's thoughts and tasks in high definition.

---

## 2. Colors: Tonal Architecture
The palette is built on a foundation of "Air and Light." We utilize a sophisticated range of cool grays and soft blues to create a sense of vastness.

### The "No-Line" Rule
**Explicit Instruction:** All junior designers are prohibited from using 1px solid borders to define sections. Layout boundaries must be defined solely through background shifts. For example, the Sidebar should utilize `surface-container-low`, while the main workspace sits on `surface`. This creates a seamless, high-end transition that mimics architectural planes rather than digital boxes.

### Surface Hierarchy & Nesting
Depth is achieved through the physical stacking of tones:
- **Base Layer:** `surface` (#f7fafc) for the primary application background.
- **Secondary Workspace:** `surface-container-low` (#eff4f8) for the navigation sidebar.
- **Active Cards:** `surface-container-lowest` (#ffffff) for task cards to provide a crisp, elevated feel.
- **Interactive Layers:** `surface-container-high` (#e2e9ee) for hovering or active states.

### The Glass & Gradient Rule
To move beyond "flat" design, floating elements (like the "New Task" FAB or dropdown menus) must use **Glassmorphism**. Apply `surface-container-lowest` at 80% opacity with a `24px` backdrop-blur. 
- **Signature Polish:** Use a subtle linear gradient on primary CTAs transitioning from `primary` (#4d626c) to `primary-dim` (#415660) at a 135-degree angle. This provides a tactile "soul" to the interface.

---

## 3. Typography: Editorial Authority
We use a dual-font system to balance professional rigor with high-end editorial flair.

*   **Display & Headlines (Manrope):** Chosen for its geometric precision and modern "tech-editorial" feel. Use `display-lg` for empty states or "Daily" headers to create a bold visual anchor.
*   **Interface & Body (Inter):** The workhorse. Inter provides maximum legibility at small sizes for task descriptions and metadata.
*   **The Scale Philosophy:** Use a "High Contrast" approach. Pair a `headline-lg` title with `body-sm` metadata. This dramatic jump in size creates a professional, intentional hierarchy that feels designed, not just populated.

---

## 4. Elevation & Depth: Tonal Layering
Traditional drop shadows are often messy. In this system, we use **Ambient Light** and **Tonal Stacking**.

*   **The Layering Principle:** Instead of a shadow, place a `surface-container-lowest` card on top of a `surface-container` background. The subtle shift in hex value provides enough contrast for the human eye to perceive elevation without visual clutter.
*   **Ambient Shadows:** If a card must "float" (e.g., during a drag-and-drop interaction), use a shadow color derived from `on-surface` at 5% opacity, with a `32px` blur and `8px` Y-offset. It should look like a soft glow, not a dark smudge.
*   **The Ghost Border:** If a boundary is required for accessibility, use `outline-variant` (#abb3b8) at **15% opacity**. It should be felt more than seen.

---

## 5. Components: The Primitive Set

### Task Cards
*   **Architecture:** No borders. Use `surface-container-lowest` background. 
*   **Corner Radius:** Use `md` (0.75rem) for a friendly yet professional softened edge.
*   **Pastel Accents:** For task categorization, apply a 4px vertical "pill" on the left edge using tertiary tones (`tertiary-fixed` or `tertiary-container`) instead of coloring the entire card. This keeps the UI "airy."

### Priority Badges
*   **High:** Use `error_container` text on `error` background (low opacity).
*   **Medium:** Use `tertiary` tones.
*   **Low:** Use `secondary` tones.
*   **Shape:** Full pill (`9999px`) with `label-sm` typography in all-caps with 0.05em tracking.

### Inputs (Search & Filtering)
*   **Styling:** Forgo the "box." Use a `surface-container-low` background with no border. 
*   **Focus State:** Transition the background to `surface-container-highest` and add a subtle `primary` underline (2px).

### Sidebar Navigation
*   **Active State:** Do not use a highlight box. Instead, use a `primary` vertical indicator line (4px width, `xl` roundedness) tucked against the left edge, and shift the text weight to `SemiBold`.

---

## 6. Do’s and Don’ts

### Do
*   **Do** use vertical white space as a separator. If you think you need a divider line, double the padding instead.
*   **Do** use `manrope` for any text larger than 24px to lean into the editorial aesthetic.
*   **Do** utilize `surface-dim` for "archived" or "completed" states to visually recede the information.

### Don't
*   **Don't** use 100% black (#000000) for text. Use `on-surface` (#2b3438) for a softer, premium reading experience.
*   **Don't** use "Standard" Material Design shadows. They are too heavy for this "Light and Airy" aesthetic.
*   **Don't** cram cards together. Every task card should have at least `16px` (1rem) of breathing room on all sides.

---

## 7. Signature Interaction: The "Soft Focus"
When a user clicks into a task to edit it, the rest of the workspace should not just darken—it should blur. Apply a `12px` backdrop-blur to the background layers to bring the user into a "Deep Work" state, emphasizing the digital curation aspect of the system.