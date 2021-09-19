# nodegui-plugin-font-icon

Use icon fonts inside QIcon with [NodeGui](https://github.com/nodegui/nodegui).

TypeScript example:

```typescript
//...
import { createFontIcon } from 'nodegui-plugin-font-icon';
//...

// Load in our custom icon font
const extraicons = path.join(__dirname, "../resources/extraicons.ttf");
QFontDatabase.addApplicationFont(extraicons);

//...

const button = new QPushButton();
const icon = createFontIcon(font, "\uEA09");  // Pocketknife icon
button.setIcon(icon);
button.setText('Font Icon');

//...
```


Install via NPM:

```
npm install nodegui-plugin-font-icon
cd node_modules/nodegui-plugin-font-icon
npm run finish-install
```

(Note: The last few steps exist to compensate for bad semantics of `postinstall` scripts.)

For the API see [src/index.ts](src/index.ts)

For a complete demo see [src/demo.ts](src/demo.ts)

# Maintainer

Simon Edwards <simon@simonzone.com>

# License

MIT

# Release Process (for maintainers)

* Make sure the version in `package.json` is correct.
* Tag the version with git (format: v1.2.3).
* Push the tag to origin.
* Wait for GitHub Action to build and release to NPM.
