import { ColorGroup, ColorRole, QApplication, QFont, QIcon } from '@nodegui/nodegui';
import addon from './addon';


export interface CreateFontIconOptions {
    /**
     * Number to scale the size of the icon by.
     */
    scale?: number;

    /**
     * Color to use when drawing the icon in Mode.Normal and State.On.
     *
     * 32bit RGBA format.
     */
    normalOnRgba?: number;

    /**
     * Color to use when drawing the icon in Mode.Disabled and State.On.
     *
     * 32bit RGBA format.
     */
    disabledOnRgba?: number;

    /**
     * Color to use when drawing the icon in Mode.Active and State.On.
     *
     * 32bit RGBA format.
     */
    activeOnRgba?: number;

    /**
     * Color to use when drawing the icon in Mode.Selected and State.On.
     *
     * 32bit RGBA format.
     */
    selectedOnRgba?: number;

    /**
     * Color to use when drawing the icon in Mode.Normal and State.Off.
     *
     * 32bit RGBA format.
     */
    normalOffRgba?: number;

    /**
     * Color to use when drawing the icon in Mode.Disabled and State.Off.
     *
     * 32bit RGBA format.
     */
    disabledOffRgba?: number;

    /**
     * Color to use when drawing the icon in Mode.Active and State.Off.
     *
     * 32bit RGBA format.
     */
     activeOffRgba?: number;

    /**
     * Color to use when drawing the icon in Mode.Selected and State.Off.
     *
     * 32bit RGBA format.
     */
    selectedOffRgba?: number;
}


/**
 * Create a QIcon to render a glyph from a font
 *
 * Glyphs are rendered centered inside the icon. By default the button
 * colors taken from the application's palette are used to rendering
 * the glyph. This can be overridden via the `options` argument.
 *
 * @param font QFont object to select the font to use when drawing the icon
 * @param text The text to render. This should generally render as one glyph.
 * @param options Optional object containing additional options.
 *
 */
export function createFontIcon(font: QFont, text: string, options?: CreateFontIconOptions): QIcon {
    options = options ?? {};

    const scale = options.scale ?? 1.0;

    const palette = QApplication.instance().palette();
    const buttonTextRgb = palette.color(ColorGroup.Active, ColorRole.ButtonText).rgba();
    const buttonTextDisabledRgb = palette.color(ColorGroup.Disabled, ColorRole.ButtonText).rgba();
    const highlightedTextRgb = palette.color(ColorGroup.Disabled, ColorRole.HighlightedText).rgba();

    const normalOnRgb = rgbaToQrgb(options.normalOnRgba) ?? buttonTextRgb;
    const disabledOnRgb = rgbaToQrgb(options.disabledOnRgba) ?? buttonTextDisabledRgb;
    const activeOnRgb = rgbaToQrgb(options.activeOnRgba) ?? buttonTextRgb;
    const selectedOnRgb = rgbaToQrgb(options.selectedOnRgba) ?? highlightedTextRgb;
    const normalOffRgb = rgbaToQrgb(options.normalOffRgba) ?? buttonTextRgb;
    const disabledOffRgb = rgbaToQrgb(options.disabledOffRgba) ?? buttonTextDisabledRgb;
    const activeOffRgb = rgbaToQrgb(options.activeOffRgba) ?? buttonTextRgb;
    const selectedOffRgb = rgbaToQrgb(options.selectedOffRgba) ?? highlightedTextRgb;

    const qiconNative = addon.FontIconCreateIcon(font.native, text, scale,
        normalOnRgb, disabledOnRgb, activeOnRgb, selectedOnRgb,
        normalOffRgb, disabledOffRgb, activeOffRgb, selectedOffRgb);
    return new QIcon(qiconNative);
}

function rgbaToQrgb(rgba: number | undefined): number | undefined {
    if (rgba === undefined) {
        return undefined;
    }
    const opacity = rgba & 0xff;
    return (rgba >> 8) | (opacity << 24);
}
