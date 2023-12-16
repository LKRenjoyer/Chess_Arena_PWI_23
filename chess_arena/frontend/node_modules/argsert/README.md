# Argsert

Simple argument type assertion.

## Install

```sh
$ npm install argsert
```

## Usage

Argsert works by mapping defined types for each argument in a method's signature to a given type. Arguments can be marked as required or optional using the <> and [] tokens. If an argument can be of multiple types simply separate each type by |.

```ts
import * as Argsert from 'argsert';
const argsert = Argsert.configure(/* your options here */);

// This method allows "email" to be the second argument.
function addUser(name, age, email) {
  argsert.assert('<string> <string|number> [string]', [name, age, email]);
}
```

## Tokens

Angle brackets <> denote a required argument square brackets [] denote an optional argument. Each definition is separated by a space. To define multiple types for an argument we use a | to denote the argument accepts multiple types.

For example the following creates definitions for a method with two arguments. The first being a string and the second an array or args.

```js
const map = '<string> [array]'
```

Multiple assertion types.

```js
const map = '<string> [string|array]'
```

Custom named argument by prefixing with "some_name:". This would replace the "first" since its the first arg with "username" instead. For complex methods with multiple overrides using the positional placeholders e.g. first, second... is likely a better option.

```js
const map = '<username:string> [array]'
```

<table>
  <tr><td>&lt;string&gt;</pre></td><td>required argument of string.</td></tr>
  <tr><td>[number]</td><td>an optional argument of number.</td></tr>
  <tr><td>[string|array]</td><td>optional argument of string or array.</td></tr>
</table>

## Options

The defaults will likely work for most use cases. You may wish to have errors not thrown which you can disable by setting "onError" to false. Or you may want to use your own validators other than the defaults that are shipped.

<table>
  <tr><td>separator</td><td>The char used to separate/denote multiple types.</td><td>|</td></tr>
  <tr><td>any</td><td>The string denoting any type is acceptable.</td><td>any</td></tr>
  <tr><td>positions</td><td>An array of argument position names (defaults to up to 7).</td><td>['first'..., 'seventh']</td></tr>
  <tr><td>expander</td><td>A RegExp or function for expanding assertion map.</td><td>/([\[<])\S+([\]>])/g</td></tr>
  <tr><td>stripper</td><td>A RegExp or function for stripping tokens/chars.</td><td>/[<>\[\]]/g</td></tr>
  <tr><td>parser</td><td>A function used to inspect an argument's type.</td><td>parseType</td></tr>
  <tr><td>strict</td><td>When false an undefined assertion config is allowed.</td><td>false</td></tr>
  <tr><td>onError</td><td>True to have errors thrown, false to return result or function to handle by user.</td><td>true</td></tr>
  <tr><td>templates</td><td>Message templates used for built in validators, useful in localization.</td><td>see Templates</td></tr>
  <tr><td>validators</td><td>A map of validator configurations.</td><td>see Validators</td></tr>
</table>

## Validators

Validators are simple configuation objects with two properties. A handler function and a key representing whether it's enabled or disabled. By default there are only three validators as listed below.

<table>
  <tr><td>unmet</td><td>Validates if less than the required number of arguments are provided. </td></tr>
  <tr><td>extra</td><td>Validates if extra arguments beyond the maxium allowed are provided.</td></tr>
  <tr><td>mismatch</td><td>Handles type mismatch failures for both required and optional arguments.</td></tr>
</table>

### Add

Adding a validator is pretty easy just provide a name and a config with a handler method. The handler should return either null if it passes or a string which will be converted to an error, an Error instance or an IArgsertValidationResult object containing the error and optionally the offending argument.

```ts
argsert.add('myValidator', {

  enabled: true,
  handler: (result) => {

    // Argsert creates two arrays of keys one for
    // required and one for optional arguments.
    // For this example validator we'll combine
    // them for this example.

    // Filter out any arg which contains
    // a type of "email".
    const keys =
      result
        .required
        .concat(result.optional);

    keys.forEach(i => {

      // Get the config for this argument.
      // A parsed argument looks like the below.

      // arg = {
      //    index: 0
      //    type: 'string'
      //    types: ['string']
      //    value: any;
      //    required: boolean;
      // }

      // Get the arg's parsed config by key.
      // The keys are basically the argument's index.
      const arg = result[i];

      // Run some check if valid return null.
      if (valid)
        return null;

      // Otherwise return the string or error along
      // with the optional offending argument
      return {
        error: new Error(`whoops ${arg.value} doesn't look right...`),
        argument: arg;
      };

      // NOTE: you can also just return the
      // error string or Error instance

    });

  }
});
```

### Enable & Disable

You can call .enable() or .disable() to define which validators are active or inactive and then toggle them back.

```ts
argsert
  .disable()              // disable all.
  .enable('mismatch');    // enable only mismatch.
```

### Validate Once

The validate once method enables only the validators you provide and uses them once then discards reverting to previous settings.

```ts
argsert
  .once('unmet') // only unmet is enabled for next validate call.
  .assert('<string> <string|number>', arguments);
```

## Types & Parser

By default the following types are supported.

+ string
+ boolean
+ number
+ array
+ function
+ object
+ regexp
+ null
+ undefined

If you wish to implement even more granular detail as to types this can be done quite easily by providing your own parser. Below is the logic for the default parser as you can see it's rather simple.

It would be trivial to implement logic for say floats or say email addresses and so on.

```ts
 function parseType(val: any) {

    if (val === null)
      return 'null';

    if ((val instanceof RegExp))
      return 'regexp';

    if (Array.isArray(val))
      return 'array';

    return typeof val;

  }
```

### Using a Custom Parser

You could also provide this in your configuration object.

```ts
argsert.option('parser', myCustomParser);
```

## Templates

These are primarily exposed for use with localization. It's important that the same number of format args are maintained. If you wish greater control you'll need to create your own validators rather than using the defaults.

<table>
  <tr><td>unmet</td><td>`expected at least %d arguments but got %d.`</td></tr>
  <tr><td>extra</td><td>`expected no more than %d arguments but got %d.`</td></tr>
  <tr><td>mismatch</td><td>`%s arg has type %s but only %s is allowed.`</td></tr>
  <tr><td>unknown</td><td>`validator %s could not be found.`</td></tr>
</table>

## Docs

See [https://blujedis.github.io/argsert/](https://blujedis.github.io/argsert/)

## Change

See [CHANGE.md](CHANGE.md)

## License

See [LICENSE](LICENSE)