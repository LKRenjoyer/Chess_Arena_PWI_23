export declare type ArgsertErrorHandler = (err: string | Error, result?: IArgsertResult) => void;
export declare type ArgsertTypeHandler = (val: any, index?: number, result?: IArgsertResult) => string;
export declare type ArgsertStripHandler = RegExp | {
    (val: any): string;
};
export declare type ArgsertExpandHandler = RegExp | {
    (val: string): string[];
};
export declare type ArgsertValidator = (result: IArgsertResult) => string | Error | IArgsertValidatorResult;
export interface IArgsertValidatorResult {
    error: string | Error;
    argument?: IArgsertArg;
}
export interface IArgsertValidator {
    enabled?: boolean;
    handler: ArgsertValidator;
}
export interface IArgsertOptions {
    separator?: string;
    any?: string;
    positions?: string[];
    expander?: ArgsertExpandHandler;
    stripper?: ArgsertStripHandler;
    parser?: ArgsertTypeHandler;
    validators?: {
        [key: string]: IArgsertValidator;
    };
    strict?: boolean;
    templates?: {
        unmet?: string;
        extra?: string;
        mismatch?: string;
        unknown?: string;
        or?: string;
    };
    onError?: boolean | ArgsertErrorHandler;
}
export interface IArgsertArg {
    index: number;
    name: string;
    type: string;
    types: string[];
    value: any;
    required: boolean;
}
export interface IArgsertResult {
    name?: string;
    keys?: number[];
    required?: number[];
    optional?: number[];
    actual?: number;
    max?: number;
    failure?: {
        error: Error;
        argument: IArgsertArg;
    };
    [key: number]: IArgsertArg;
}
export interface IArgsert {
    /**
    * Gets an option.
    *
    * @param key the option key to get.
    */
    option(key: string): any;
    /**
     * Sets an option
     *
     * @param key the option name.
     * @param val the value for the option.
     */
    option(key: string, val: any): IArgsert;
    /**
     * Adds a validator to the collection.
     *
     * @param name the of the validator to add.
     * @param validator the validator config to add.
     */
    add(name: string, validator: IArgsertValidator): IArgsert;
    /**
     * Removes a validator from the collection.
     *
     * @param name the name of the validator to remove.
     */
    remove(name: string): IArgsert;
    /**
     * Enables validators by name.
     *
     * @param validator list of validators to enable.
     */
    enable(...validator: string[]): IArgsert;
    /**
     * Disables validators by name.
     *
     * @param validator list of validators to disable.
     */
    disable(...validator: string[]): IArgsert;
    /**
     * Gets enabled validators.
     */
    enabled(): string[];
    /**
     * Gets disabled validators.
     */
    disabled(): string[];
    /**
     * Enables listed validators disabling all others, then resets after validate runs.
     *
     * @param validators the list of validators to run once.
     */
    once(...validators: string[]): IArgsert;
    /**
     * Validates values against assertion map using specified validator.
     *
     * @example .assert('<string> <number>', ['name', 40], 2)
     *
     * @param map the token map for type assertion checks.
     * @param values actual values from the method min args or arguments object.
     * @param len specifies argument length or uses values length.
     */
    validate(map: string, values?: object | any[], validator?: string | ArgsertValidator): IArgsertResult;
    /**
     * Validates values against assertion map using specified validator.
     *
     * @example .assert('<string> <number>', ['name', 40], 2)
     *
     * @param map the token map for type assertion checks.
     * @param values actual values from the method min args or arguments object.
     * @param len specifies argument length or uses values length.
     */
    validate(map: string, values?: object | any[], len?: number, validator?: string | ArgsertValidator): IArgsertResult;
    /**
    * Validates values against assertion map using all enabled validators.
    *
    * @example .assert('<string> <number>', ['name', 40], 2)
    *
    * @param map the token map for type assertion checks.
    * @param values actual values from the method min args or arguments object.
    * @param validator manually call specific validator or pass validator function.
    */
    assert(map: string, values?: object | any[], validator?: string | ArgsertValidator): IArgsertResult;
    /**
     * Validates values against assertion map using all enabled validators.
     *
     * @example .assert('some_method', '<string> <number>', ['name', 40], 2)
     *
     * @param name the method name calling assert.
     * @param map the token map for type assertion checks.
     * @param values actual values from the method min args or arguments object.
     * @param validator manually call specific validator or pass validator function.
     */
    assert(name: string, map: string, values?: object | any[], validator?: string | ArgsertValidator): IArgsertResult;
    /**
     * Validates values against assertion map using all enabled validators.
     *
     * @example .assert('<string> <number>', ['name', 40], 2)
     *
     * @param map the token map for type assertion checks.
     * @param values actual values from the method min args or arguments object.
     * @param len specifies argument length or uses values length.
     * @param validator manually call specific validator or pass validator function.
     */
    assert(map: string, values?: object | any[], len?: number, validator?: string | ArgsertValidator): IArgsertResult;
    /**
     * Validates values against assertion map using all enabled validators.
     *
     * @example .assert('some_method', '<string> <number>', ['name', 40], 2)
     *
     * @param name the method name calling assertion.
     * @param map the token map for type assertion checks.
     * @param values actual values from the method min args or arguments object.
     * @param len specifies argument length or uses values length.
     * @param validator manually call specific validator or pass validator function.
     */
    assert(name: string, map: string, values?: object | any[], len?: number, validator?: string | ArgsertValidator): IArgsertResult;
    /**
     * Resets once and enabled/disabled to defaults.
     */
    reset(): IArgsert;
}
