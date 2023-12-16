"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const util_1 = require("util");
function configure(options) {
    let methods = {};
    const DEFAULTS = {
        separator: '|',
        any: 'any',
        expander: /([\[<])\S+([\]>])/g,
        stripper: /[<>\[\]]/g,
        parser: parseType,
        strict: false,
        onError: true,
        // The only reason you'll likely need to
        // modify the below would be if you're using
        // localization and wish to use the default
        // validators.
        // Friendly names for argument positions.
        positions: [
            'first', 'second', 'third',
            'fourth', 'fifth', 'sixth',
            'seventh'
        ],
        // Exposed for localization purposes.
        // When modifying maintain the same format args.
        templates: {
            unmet: `expected at least %s argument(s) but got %s.`,
            extra: `expected no more than %s argument(s) but got %s.`,
            mismatch: `%s arg has type %s but only %s is allowed.`,
            unknown: `validator %s could not be found.`,
            or: `or`
        },
        // Validators in order of execution.
        validators: null
    };
    options = Object.assign({}, DEFAULTS, options);
    options.validators = options.validators || {
        unmet: {
            handler: unmetArgs
        },
        extra: {
            handler: extraArgs
        },
        mismatch: {
            handler: mismatchArgs
        }
    };
    let _once;
    const defaultEnabled = enabled();
    const defaultDisabled = disabled();
    // VALIDATORS //
    function unmetArgs(result) {
        const name = result.name ? result.name + ' ' : '';
        if (result.actual < result.required.length)
            return name + util_1.format(options.templates.unmet, result.required.length, result.actual);
        return null;
    }
    function extraArgs(result) {
        const name = result.name ? result.name + ' ' : '';
        if (result.actual > result.max)
            return name + util_1.format(options.templates.extra, result.max, result.actual);
        return null;
    }
    function mismatchArgs(result) {
        const keys = result.required.concat(result.optional);
        // Iterate keys validate each argument.
        for (const key of keys) {
            const arg = result[key];
            const matches = arg.types.filter(t => t === options.any || t === arg.type);
            if (matches.length)
                continue;
            const name = result.name ? result.name + ' ' : '';
            const template = options.templates.mismatch;
            let pos = arg.name ? arg.name : options.positions[arg.index];
            const orStr = options.templates.or;
            return {
                error: name + util_1.format(template, pos, arg.type, arg.types.join(` ${orStr} `)),
                argument: arg
            };
        }
        return null;
    }
    // HELPERS //
    /**
     * Handles Argsert errors.
     *
     * @param err the error message to be handled.
     * @param result the parsed result object.
     */
    function handleError(err, result) {
        if (typeof err === 'string') {
            err = new Error(err);
            let stack = err.stack.split('\n');
            stack = [...stack.slice(0, 1), ...stack.slice(1)];
            err.stack = stack.join('\n');
        }
        result.failure.error = err;
        if (!options.onError)
            return result;
        if (typeof options.onError === 'function') {
            options.onError(err, result);
            return result;
        }
        throw err;
    }
    /**
     * Method for guessing type of value.
     *
     * @param val the value to inspect for getting type.
     */
    function parseType(val) {
        if (val === null)
            return 'null';
        if ((val instanceof RegExp))
            return 'regexp';
        if (Array.isArray(val))
            return 'array';
        return typeof val;
    }
    /**
     * Strips sting or <, >, [, ] tokens which denote required/optional.
     *
     * @param str the string to strip.
     */
    function strip(str) {
        if (typeof options.stripper === 'function')
            return options.stripper(str);
        return (str || '').replace(options.stripper, '').trim();
    }
    /**
     * Expand string into segments by spaces not encapsulated by quotes..
     *
     * @example 'install --dir "/some/path" -f' >> ['install', '--dir', '/some/path', '-f']
     *
     * @param tokens the arg string to split to array.
     * @param ignores when matched ignore spaces within these chars.
     * @param safe same as match except these chars will be included in result.
     */
    function expand(tokens) {
        if (typeof options.expander === 'function')
            return options.expander(tokens);
        return (tokens || '').trim().match(options.expander);
    }
    /**
     * Sets state for array of validators.
     *
     * @param state the enabled state.
     * @param validators array of validators to be set.
     * @param allowAll when true set all on empty validators.
     */
    function toggleValidators(state, validators, allowAll = false) {
        const keys = Object.keys(options.validators);
        if (!validators.length && allowAll)
            validators = keys;
        validators.forEach(k => {
            if (~keys.indexOf(k))
                options.validators[k].enabled = state;
            else
                console.warn(options.templates.unknown, k);
        });
    }
    /**
     * Normalize assertion arguments.
     *
     * @param map the string map of assertion tokens.
     * @param values the argument values to validate.
     * @param len optional length override.
     */
    function normalize(map, values, len) {
        values = [].slice.call(values || []);
        let args = values;
        // Trim trailing undefined.
        while (args.length && args[args.length - 1] === undefined)
            args.pop();
        len = len || args.length;
        // Expand to an array to tokens.
        let expanded = expand(map);
        let repeatIndex;
        let repeatVal;
        expanded = expanded.map((v, i) => {
            if (~v.indexOf('...')) {
                v = v.replace('...', '');
                repeatIndex = i;
                repeatVal = v;
            }
            return v;
        });
        if (typeof repeatIndex === 'number' && len > 0) {
            repeatIndex = Math.max(0, len - (repeatIndex + 1));
            while (repeatIndex) {
                expanded.push(repeatVal);
                repeatIndex--;
            }
        }
        // If not strict add "any" for missing configs.
        if (expanded.length < len && !options.strict)
            while (expanded.length < len)
                expanded.push(`[${options.any}]`);
        return {
            args,
            expanded,
            len,
            values
        };
    }
    /**
     * Parse the assersion map against values.
     *
     * @param name the method name calling assert.
     * @param expanded the normalized expanded assertion map.
     * @param values the argument values to be inspected.
     * @param len optional length override.
     */
    function parseMap(name, expanded, values, len) {
        // Map to object of types and values.
        return expanded.reduce((a, c, i) => {
            const req = c.startsWith('<');
            a.keys.push(i);
            // Might do more with multiple names in future.
            // for now just select the first.
            c = strip(c);
            const lastIdx = c.lastIndexOf(':');
            let names = [], types;
            if (lastIdx >= 0) {
                names = c.slice(0, lastIdx).split(':');
                types = c.slice(lastIdx + 1).split(options.separator);
            }
            else {
                types = c.split(options.separator);
            }
            let name = names[0] || options.positions[i];
            a[i] = {
                index: i,
                name: name,
                required: req,
                types: types,
                value: values[i],
                type: parseType(values[i])
            };
            // [] or <> passed with no content.
            // If not strict just add any type.
            if (!a[i].types.length && !options.strict)
                a[i].types = [options.any];
            // Allow setting undefined as valid type
            // for optional args when not strict mode.
            if (!a[i].required && a[i].type === 'undefined' && !options.strict)
                a[i].types.push('undefined');
            if (!a[i].required && a[i].type === 'null' && !options.strict)
                a[i].types.push('null');
            if (req)
                a.required.push(i);
            if (!req)
                a.optional.push(i);
            a.max += 1;
            return a;
        }, { name: name, keys: [], max: 0, required: [], optional: [], actual: len });
    }
    // API //
    function option(key, val) {
        if (typeof val === 'undefined')
            return options[key];
        options[key] = val;
        return methods;
    }
    function enable(...validators) {
        _once = undefined;
        toggleValidators(true, validators, true);
        return methods;
    }
    function disable(...validators) {
        _once = undefined;
        toggleValidators(false, validators, true);
        return methods;
    }
    function enabled() {
        if (_once)
            return _once;
        return Object.keys(options.validators).filter(k => options.validators[k].enabled !== false);
    }
    function disabled() {
        return Object.keys(options.validators).filter(k => options.validators[k].enabled === false);
    }
    function add(name, validator) {
        options.validators[name] = validator;
        if (validator.enabled === false && !~defaultDisabled.indexOf(name))
            defaultDisabled.push(name);
        if (validator.enabled !== false && !~defaultEnabled.indexOf(name))
            defaultEnabled.push(name);
        return methods;
    }
    function remove(name) {
        delete options.validators[name];
        if (~defaultDisabled.indexOf(name))
            defaultDisabled.splice(defaultDisabled.indexOf(name), 1);
        if (~defaultEnabled.indexOf(name))
            defaultEnabled.splice(defaultEnabled.indexOf(name), 1);
        return methods;
    }
    function once(...validators) {
        if (!validators.length)
            return methods;
        disable();
        _once = validators.slice(0);
        return methods;
    }
    function assert(name, map, values, len, validator) {
        // map is first arg shift.
        if (name && name.length && (~name.indexOf('[') || ~name.indexOf('<'))) {
            validator = len;
            len = values;
            values = map;
            map = name;
            name = undefined;
        }
        try {
            if (!map || !map.length)
                return null;
            if (typeof len === 'function' || typeof len === 'string') {
                validator = len;
                len = undefined;
            }
            // Get normalized arguments.
            const normalized = normalize(map, values, len);
            // Map to object of types and values.
            const result = parseMap(name, normalized.expanded, normalized.args, normalized.len);
            // Get the validator keys to apply.
            let validators;
            // Check if user specified specific validator.
            if (!validator)
                validators = _once && _once.length ? _once : Object.keys(options.validators);
            else
                validators = [validator];
            let failed;
            // Iterate validators & handle failures.
            while (!failed && validators.length) {
                let _validator = validators.shift();
                let _failed;
                // User defined validator specified.
                if (typeof _validator === 'function') {
                    _failed = _validator(result);
                }
                // Lookup validator and get handler.
                else {
                    _validator = options.validators[_validator];
                    if (!_validator || _validator.enabled === false)
                        continue;
                    _failed = _validator.handler(result);
                }
                if (typeof _failed === 'string' || (_failed instanceof Error)) {
                    failed = {
                        error: _failed,
                        argument: null
                    };
                }
                else {
                    failed = _failed;
                }
            }
            // Set once back to default.
            _once = undefined;
            // Handler if error.
            if (failed) {
                result.failure = failed;
                return handleError(failed.error, result);
            }
            return result;
        }
        catch (ex) {
            console.warn(ex.stack);
        }
    }
    function reset() {
        _once = undefined;
        disable(...defaultDisabled);
        enable(...defaultEnabled);
        return methods;
    }
    methods.option = option;
    methods.add = add;
    methods.remove = remove;
    methods.enable = enable;
    methods.disable = disable;
    methods.enabled = enabled;
    methods.disabled = disabled;
    methods.once = once;
    methods.assert = assert;
    methods.reset = reset;
    return methods;
}
exports.configure = configure;
//# sourceMappingURL=argsert.js.map